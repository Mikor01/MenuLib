#pragma once
#include "IMenuItem.hpp"
#include <stdexcept>
#include <string>
#include <type_traits>
#include <functional>

namespace mr {
    /**
    * @brief Template Menu Slider item class.
    *
    * Handles value incrementing and decrementing for numeric types (int, float, double, etc.)
    * @tparam T Numeric type to be controlled (e.g. int, float, double)
    */
    template <typename T>
    class MenuSlider : public IMenuItem {
        static_assert(std::is_arithmetic<T>::value, "MenuSlider: can only be used with numeric types.");

        private:
            /**
            * @brief Current value
            */
            T m_value;
            /**
            * @brief Minimum value possible to set
            */
            T m_min;
            /**
            * @brief Maximum value possible to set
            */
            T m_max;
            /**
            * @brief Step with which the value increments or decrements
            */
            T m_step;
            /**
            * @brief Base display label without respect to value
            */
            std::string m_baseLabel;
            /**
            * @brief Function attached for the item to execute passing the value
            */
            std::function<void(T)> m_func;
            /**
            * @brief helper function to set full label with baseLabel and current value
            */
            void updateLabel() {
                std::string name = m_baseLabel + " < " + std::to_string(m_value) + " >";
                IMenuItem::setLabel(name);
            }

        public:

            /**
            * @brief Placeholder constructor
            *
            * Creates an instance with given label, default constrains, steps and no function
            *
            * @param label Display text label
            */
            MenuSlider(const std::string& label)
                : IMenuItem(label), m_baseLabel(label), m_value(0), m_min(0), m_max(100), m_step(1), m_func(nullptr)
            {
                if(label.empty()){
                    throw std::invalid_argument("MenuSlider: Label cannot be empty");
                }
                updateLabel();
            }

            /**
            * @brief Parametric constructor
            *
            * Creates an instance with given label, initial value,
            * minimum and maximum constrains, given step size and attached function to pass value to
            *
            * @param label Display text label
            * @param val initial value
            * @param min minimum value constrain
            * @param max maximum value constrain
            * @param step step size
            * @param func Function to execute when selected
            */
            MenuSlider(const std::string& label, T val, T min,
                       T max, T step,const std::function<void(T)>& func)
                :IMenuItem(label), m_baseLabel(label), m_value(val), m_min(min), m_max(max), m_step(step), m_func(func)
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

            /**
            * @brief Indicates whether this item represents a terminal menu entry.
            *
            * @return true if selecting this item does not lead to another menu,
            *         false if it leads to a submenu.
            */
            bool isEnd() const override{
                return true;
            }

            /**
            * @brief overrides onSelect in a way that the slider ignores select action
            *
            * @param navigator Pointer to the menu navigator
            */
            void onSelect(MenuNavigator* navigator) override {}

            /**
            * @brief decrement current value
            *
            * @param navigator Pointer to the menu navigator
            */
            void onLeft(MenuNavigator* navigator) override{
                if (m_value - m_step >= m_min){
                    m_value -= m_step;
                    updateLabel();
                    if (m_func){
                        m_func(m_value);
                    }
                }
            }
            /**
            * @brief increment current value
            *
            * @param navigator Pointer to the menu navigator
            */
            void onRight(MenuNavigator* navigator) override{
                if (m_value + m_step <= m_max){
                    m_value += m_step;
                    updateLabel();
                    if (m_func){
                        m_func(m_value);
                    }
                }
            }

            /**
            * @brief sets display label with respect to current value
            *
            * @param label new display label to set
            */
            void setLabel(const std::string& label) override{
                if(!label.empty()){
                    m_baseLabel = label;
                    updateLabel();
                }
            }

            /**
            * @brief sets minimum value the slider can have
            *
            * @param min new minimum value
            */
            void setMin(T min){
                if(min >= m_max)
                {
                    return;
                }

                m_min = min;

                // auto-correct value if it is now out of bounds, clamp it to the min
                if(m_value < min)
                {
                    m_value = min;
                    updateLabel();
                }
            }

            /**
            * @brief sets maximum value the slider can have
            *
            * @param max new maximum value
            */
            void setMax(T max){
                if(max <= m_min)
                {
                    return;
                }

                m_max = max;

                // auto-correct value if it is now out of bounds, clamp it to the max
                if(m_value > max)
                {
                    m_value = max;
                    updateLabel();
                }
            }

            /**
            * @brief sets step value the slider increments or decrements by
            *
            * @param step new minimum value
            */
            void setStep(T step){
                if(step <= 0)
                {
                    return;
                }

                m_step = step;
            }

            /**
            * @brief sets current value the slider has
            *
            * @param value new value
            */
            void setValue(T value){

                // clamping between bounds of max and min
                if (value < m_min){
                    value = m_min;
                }
                if (value > m_max){
                    value = m_max;
                }

                if (m_value != value) {
                    m_value = value;
                    updateLabel();
                    if (m_func){
                        m_func(m_value);
                    }
                }
            }
    };
}
