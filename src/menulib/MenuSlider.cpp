#include "menulib/MenuSlider.hpp"
#include "menulib/IMenuItem.hpp"
#include <string>

namespace mr{
    MenuSlider::MenuSlider(std::string label, int val, int min, int max, int step, std::function<void(int)>& func)
        : IMenuItem(label), m_baseLabel(label), m_value(val),
        m_min(min), m_max(max), m_step(step), m_func(func)
    {
        if(label.empty()){
            throw std::invalid_argument("MenuToggle: Label cannot be empty");
        }
        if(!func){
            throw std::invalid_argument("MenuToggle: Function cannot be null");
        }
        updateLabel();
    }

    bool MenuSlider::isEnd() const{
        return true;
    }

    void MenuSlider::onLeft(MenuNavigator* navigator)  {
        if (m_value - m_step >= m_min) {
            m_value -= m_step;
            updateLabel();
            if (m_func){
                m_func(m_value);
            }
        }
    }

    void MenuSlider::onRight(MenuNavigator* navigator) {
        if (m_value + m_step <= m_max) {
            m_value += m_step;
            updateLabel();
            if (m_func) m_func(m_value);
        }
    }

    void MenuSlider::setLabel(const std::string& label) {
            if(!label.empty()) {
                m_baseLabel = label;
                updateLabel();
            }
        }
}
