#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <cstdlib>

#include "menulib/MenuPage.hpp"
#include "menulib/MenuOption.hpp"
#include "menulib/MenuNavigator.hpp"
#include "menulib/MenuToggle.hpp"
#include "menulib/MenuSlider.hpp"

#ifdef _WIN32
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>
#endif
//getch_ 0 witout echo 1 with echo
char getch_(int echo) {
    char ch;

#ifdef _WIN32
    if (echo) {
        ch = _getche(); // get char with echo
    } else {
        ch = _getch();  // get char without echo
    }
#else
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt); // grab old settings
    newt = oldt;
    newt.c_lflag &= ~ICANON;        // disable buffer

    if (echo) {
        newt.c_lflag |= ECHO;
    } else {
        newt.c_lflag &= ~ECHO;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &newt); // apply new settings
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt); // restore old settings
#endif

    return ch;
}

void clear(){
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

bool isRunning = true;
bool soundEnabled = true;
int volumeLevel = 50;

void videoSettings(){
    std::cout << "\n[!] Video settings changed!\n";
    std::cout << "Press any key to continue...";
    getch_(0);
}

void startGame(){
    std::cout << "\n[!] Game started!\n";
    std::cout << "Press any key to continue...";
    getch_(0);
}

void stop(){
    isRunning = false;
}

void onSoundChange(bool state){
    soundEnabled = state;
}

void onVolumeChange(int val){
    volumeLevel = val;
}

int main() {

    //forward declaration of menu
    mr::MenuPage* mainMenu = nullptr;

    try {
        mainMenu = new mr::MenuPage("Main Menu", nullptr);

        mr::MenuPage* settingsMenu = new mr::MenuPage("Settings", mainMenu);

        settingsMenu->addItem(new mr::MenuToggle("Sound", soundEnabled, onSoundChange));

        settingsMenu->addItem(new mr::MenuSlider("Volume", volumeLevel, 0, 100, 5, onVolumeChange));

        settingsMenu->addItem(new mr::MenuOption("Video Settings", videoSettings));

        mainMenu->addItem(new mr::MenuOption("Start Game", startGame));
        mainMenu->addItem(settingsMenu);
        mainMenu->addItem(new mr::MenuOption("Exit", stop));

        mr::MenuNavigator nav(mainMenu);

        while (isRunning) {
            clear();

            std::cout << "--- " << nav.getCurrentTitle() << " ---\n\n";

            const auto& items = nav.getCurrentItems();
            int index = nav.getCurrentIndex();

            for (size_t i = 0; i < items.size(); ++i) {
                if (i == index) {
                    std::cout << " > " << items[i]->getLabel() << " <\n";
                } else {
                    std::cout << "   " << items[i]->getLabel() << "\n";
                }
            }

            std::cout << "\n-----------------------------\n";
            std::cout << "[W] Up  [S] Down  [A] Left  [D] Right  [E] Select  [B] Back\n";
            std::cout << "Selection: ";

            char input;
            //std::cin >> input;
            input = getch_(0);
            input = std::tolower(input);

            switch (input) {
                case 'w': nav.previous(); break;
                case 's': nav.next(); break;
                case 'a': nav.left(); break;
                case 'd': nav.right(); break;
                case 'e': nav(); break;
                case 'b': nav.back(); break;
                default: break;
            }
        }
    }
    catch (const std::exception& e) {
        clear();
        std::cerr << "Error: " << e.what() << "\n";
        delete mainMenu;
        return 1;
    }

    std::cout << "\nGoodbye!\n";
    delete mainMenu;

    return 0;
}
