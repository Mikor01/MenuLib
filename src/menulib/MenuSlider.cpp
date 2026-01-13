#include "menulib/MenuSlider.hpp"
#include "menulib/IMenuItem.hpp"

namespace mr{

    MenuSlider::MenuSlider(const std::string& label)
        : IMenuItem(label), m_baseLabel(label), m_value(0), m_min(0), m_max(100), m_step(1), m_func(nullptr)
    {
        if(label.empty()){
            throw std::invalid_argument("MenuSlider: Label cannot be empty");
        }
        updateLabel();
    }

    MenuSlider::MenuSlider(const std::string& label, int val, int min, int max,
                           int step, const std::function<void(int)>& func)
        : IMenuItem(label), m_baseLabel(label), m_value(val), m_min(min), m_max(max), m_step(step), m_func(func)
    {
        if(label.empty()){
            throw std::invalid_argument("MenuSlider: Label cannot be empty");
        }
        if(!func){
            throw std::invalid_argument("MenuSlider: Function cannot be null");
        }
        if(min >= max){
            throw std::invalid_argument("MenuSlider: Max cannot be equal or less than Min");
        }
        if(val < min || val > max) {
            throw std::invalid_argument("MenuSlider: Initial value cannot be out of bounds");
        }
        if(step <= 0) {
            throw std::invalid_argument("MenuSlider: Step must be positive integer");
        }
        updateLabel();
    }

    bool MenuSlider::isEnd() const{
        return true;
    }

    void MenuSlider::onLeft(MenuNavigator* navigator){
        if (m_value - m_step >= m_min){
            m_value -= m_step;
            updateLabel();
            if (m_func){
                m_func(m_value);
            }
        }
    }

    void MenuSlider::onRight(MenuNavigator* navigator){
        if (m_value + m_step <= m_max){
            m_value += m_step;
            updateLabel();
            if (m_func){
                m_func(m_value);
            }
        }
    }

    void MenuSlider::setLabel(const std::string& label){
        if(!label.empty()){
            m_baseLabel = label;
            updateLabel();
        }
    }

    void MenuSlider::setMin(int min){
        if(min >= m_max)
        {
            return;
        }

        m_min = min;

        if(m_value < min)
        {
            m_value = min;
            updateLabel();
        }
    }

    void MenuSlider::setMax(int max){
        if(max <= m_min)
        {
            return;
        }

        m_max = max;

        if(m_value > max)
        {
            m_value = max;
            updateLabel();
        }
    }

    void MenuSlider::setStep(int step){
        if(step <= 0)
        {
            return;
        }

        m_step = step;
    }

    void MenuSlider::setValue(int val) {
        if (val < m_min){
            val = m_min;
        }
        if (val > m_max){
            val = m_max;
        }

        if (m_value != val) {
            m_value = val;
            updateLabel();
            if (m_func){
                m_func(m_value);
            }
        }
    }

}
