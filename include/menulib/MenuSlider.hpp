#pragma once
#include "IMenuItem.hpp"
#include <functional>
#include <stdexcept>
#include <string>

namespace mr {
    /**
    * @brief Menu Slider item class.
    *
    * Menu slider item is a class for elements which handle value incrementing and decrementing
    */
    class MenuSlider : public IMenuItem {
    private:
        /**
        * @brief Current value
        */
        int m_value;
        /**
        * @brief Minimum value possible to set
        */
        int m_min;
        /**
        * @brief Maximum value possible to set
        */
        int m_max;
        /**
        * @brief Step with which the value increments or decrements
        */
        int m_step;
        /**
        * @brief Base display label without respect to value
        */
        std::string m_baseLabel;
        /**
        * @brief Function attached for the item to execute passing the value
        */
        std::function<void(int)> m_func;
        /**
        * @brief helper function to set full label with baseLabel and current value
        */
        void updateLabel() {
            std::string name = m_baseLabel + " < " + std::to_string(m_value) + " >";
            IMenuItem::setLabel(name);
        }

    public:
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
        MenuSlider(std::string label, int val, int min, int max, int step,const std::function<void(int)>& func);

        /**
        * @brief Indicates whether this item represents a terminal menu entry.
        *
        * @return true if selecting this item does not lead to another menu,
        *         false if it leads to a submenu.
        */
        bool isEnd() const override;

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
        void onLeft(MenuNavigator* navigator) override;
        /**
        * @brief increment current value
        *
        * @param navigator Pointer to the menu navigator
        */
        void onRight(MenuNavigator* navigator) override;

        /**
        * @brief sets display label with respect to current value
        *
        * @param new display label to set
        */
        void setLabel(const std::string& label) override;
    };
}
