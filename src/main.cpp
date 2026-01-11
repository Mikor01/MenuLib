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

bool isRunning = true;
bool soundEnabled = true;
int volumeLevel = 50;

void videoSettings(){
    std::cout << "\n[!] Video settings changed!\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void startGame(){
    std::cout << "\n[!] Game started!\n";
    std::cout << "Press Enter to continue...";
    std::cin.ignore();
    std::cin.get();
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
            std::system("clear");

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
            std::cin >> input;
            input = std::tolower(input);

            switch (input) {
                case 'w': --nav; break;
                case 's': ++nav; break;
                case 'a': nav.left(); break;
                case 'd': nav.right(); break;
                case 'e': nav(); break;
                case 'b': nav.back(); break;
                default: break;
            }
        }
    }
    catch (const std::exception& e) {
        std::system("clear");
        std::cerr << "Error: " << e.what() << "\n";
        delete mainMenu;
        return 1;
    }

    std::cout << "Goodbye!\n";
    delete mainMenu;

    return 0;
}
