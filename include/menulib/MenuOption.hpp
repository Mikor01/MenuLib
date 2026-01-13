#pragma once
#include "IMenuItem.hpp"
#include <stdexcept>
#include <string>
#include <functional>

namespace mr{
    /**
    * @brief Menu Page item class.
    *
    * Menu option item is a class for elements which will contain pointer to a function to execute
    */
    class MenuOption : public IMenuItem{
        private:

            /**
            * @brief Function attached for the item to execute
            */
            std::function<void()> m_func {};
        public:

            /**
            * @brief Parametric constructor
            *
            * Creates an instance with given label and function to execute
            *
            * @param label Display text label
            * @param func Function to execute when selected
            */
            MenuOption(const std::string& label, const std::function<void()>& func);

            /**
            * @brief Executes the function associated with this menu option.
            *
            * Typically called when the item is selected.
            */
            void execute() const;

            /**
            * @brief Indicates whether this item represents a terminal menu entry.
            *
            * @return true if selecting this item does not lead to another menu,
            *         false if it leads to a submenu.
            */
            bool isEnd() const override;

            /**
            * @brief When selected executes the function by calling execute()
            *
            * @param navigator Pointer to the menu navigator
            */
            void onSelect(MenuNavigator* navigator) override;

    };
}
