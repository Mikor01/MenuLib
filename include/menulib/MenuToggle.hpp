#pragma once
#include <functional>
#include <stdexcept>
#include "IMenuItem.hpp"

namespace mr{
    /**
    * @brief Menu Toggle item class.
    *
    * Menu toggle item is a class for elements which handle value toggling functionality
    */
    class MenuToggle : public IMenuItem{
        private:
            /**
            * @brief State of the toggle element
            */
            bool m_state;
            /**
            * @brief Display label of the menu item.
            */
            std::string m_baseLabel;
            /**
            * @brief Function attached for the item to execute passing the toggled bool
            */
            std::function<void(bool)> m_func {};

            /**
            * @brief updates main label which is displayed by adding state to base name
            */
            void updateLabel(){
                std::string name = m_baseLabel + (m_state ? " [ON]" : " [OFF]");
                IMenuItem::setLabel(name);
            }
        public:

            /**
            * @brief Parametric constructor
            *
            * Creates an instance with given label, initial state and function to execute
            *
            * @param label Display text label
            * @param initialState initial state of controlled bool
            * @param func Function to execute when selected
            */
            MenuToggle(const std::string& label, bool initialState, const std::function<void(bool)>& func);

            /**
            * @brief Indicates whether this item represents a terminal menu entry.
            *
            * @return true if selecting this item does not lead to another menu,
            *         false if it leads to a submenu.
            */
            bool isEnd() const override;

            /**
            * @brief When selected toggles state, and executes held fuction with the new state
            *
            * @param navigator Pointer to the menu navigator
            */
            void onSelect(MenuNavigator* navigator) override;

            /**
            * @brief updates display label with respect to the current state
            *
            * @param label new display label to set
            */
            void setLabel(const std::string& label) override;

    };
}
