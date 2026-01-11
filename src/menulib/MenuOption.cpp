#include "menulib/MenuOption.hpp"
#include "menulib/IMenuItem.hpp"


namespace mr{
    MenuOption::MenuOption(const std::string& label, const std::function<void()>& func) : IMenuItem(label), m_func(func){
        if(label.empty()){
            throw std::invalid_argument("MenuOption: Label cannot be empty");
        }
        if(!func){
            throw std::invalid_argument("MenuOption: Function cannot be null");
        }
    };

    void MenuOption::execute() const {
        if(m_func)
        {
            m_func();
        }
    }

    void MenuOption::onSelect(MenuNavigator* navigator){
        MenuOption::execute();
    }

    bool MenuOption::isEnd() const {
        return true;
    };

}
