#include "menulib/MenuToggle.hpp"
#include "menulib/IMenuItem.hpp"
#include <string>


namespace mr{
    MenuToggle::MenuToggle(const std::string& label, bool initialState, const std::function<void(bool)>& func)
        : IMenuItem(label), m_baseLabel(label),
        m_state(initialState), m_func(func)
    {
        if(label.empty()){
            throw std::invalid_argument("MenuToggle: Label cannot be empty");
        }
        if(!func){
            throw std::invalid_argument("MenuToggle: Function cannot be null");
        }
        if(!initialState)
        {
            m_state = false;
        }
        updateLabel();
    };

    void MenuToggle::setLabel(const std::string& label){
        if(!label.empty())
        {
            m_baseLabel = label;

            updateLabel();
        }
    }

    void MenuToggle::onSelect(MenuNavigator* navigator){
        m_state = !m_state;
        updateLabel();
        if(m_func){
            m_func(m_state);
        }
    }

    bool MenuToggle::isEnd() const {
        return true;
    }

}
