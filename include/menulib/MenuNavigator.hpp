#pragma once
#include "MenuPage.hpp"
#include <stdexcept>
#include <vector>
#include <string>

namespace mr{
    /**
    * @brief Controls navigation between menu pages and selection of items.
    *
    * MenuNavigator maintains the current menu page and highlighted item,
    * and provides operations for navigating and selecting menu entries.
    */
    class MenuNavigator{
        private:
            MenuPage* m_root {};
            MenuPage* m_currentMenu{};
            int m_currentIndex{};

        public:
            /**
            * @brief Parametric Menu Navigator constructor
            *
            * Creates a MenuNavigator instance with a root attached
            *
            * @param root pointer to the root menu page (the main menu page)
            */
            MenuNavigator(MenuPage* root);

            /**
             * @brief highlights next item in menu page.
             */
            void next();

            /**
             * @brief highlights previous item in menu page.
             */
            void previous();

            /**
             * @brief selects highlighted item in menu page
             *
             * If selected item is a menu page instance it enters the submenu
             * If selected item is a menu option instance it exexcutes the function within.
             */
            void select();

            /**
             * @brief changes current menu page to the one set as parent of menu page.
             */
            void back();

            /**
            * @brief Returns the items of the current menu page.
            *
            * @return Reference to the vector of menu items in the current page.
            */
            const std::vector<IMenuItem*>& getCurrentItems() const;


            /**
            * @brief Change current menu page to selected or previous (parent)
            *
            * @param currentMenu pointer to the menu page
            */
            void setCurrentMenu(MenuPage* currentMenu);

            /**
            * @brief Returns current index (which item is highlighted)
            *
            * @return highlighted item index
            */
            int getCurrentIndex() const;

            /**
            * @brief Returns highlighted item's label
            *
            * @return highlighted item's display label
            */
            const std::string& getCurrentTitle() const;

            /**
            * @brief highlights next item in menu page.
            * This is just a "forced" EXAMPLE of operator overloading being used.
            * Otherwise, overloading this operator does not make much sense in this context.
            *
            * @return reference to the MenuNavigator instance.
            */
            MenuNavigator& operator++();
            /**
            * @brief highlights previous item in menu page.
            * This is just a "forced" EXAMPLE of operator overloading being used.
            * Otherwise, overloading this operator does not make much sense in this context.
            *
            * @return reference to the MenuNavigator instance.
            */
            MenuNavigator& operator--();
            /**
            * @brief selects highlighted item in menu page.
            *
            */
            void operator()();

            /**
             * @brief moves slider type objects value to the left (decrement).
             */
            void left();

            /**
             * @brief moves slider type objects value to the right (increment).
             */
            void right();
    };
}
