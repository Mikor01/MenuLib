#include "menulib/MenuToggle.hpp"

namespace mr{
    MenuToggle::MenuToggle(const std::string& label, bool initialState, const std::function<void(bool)>& func)
        : IMenuItem(label), m_state(initialState), m_baseLabel(label), m_func(func)
    {
        if(label.empty()){
            throw std::invalid_argument("MenuToggle: Label cannot be empty");
        }
        if(!func){
            throw std::invalid_argument("MenuToggle: Function cannot be null");
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
