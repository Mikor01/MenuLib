#pragma once
#include "IMenuItem.hpp"
#include <stdexcept>
#include <string>
#include <vector>

namespace mr{

    /**
    * @brief Menu Page item class.
    *
    * Menu page item is a class for elements which will contain other submenus and actions inside
    */
    class MenuPage : public IMenuItem{
        private:

            /**
            * @brief Items contained within this menu page.
            *
            * Contains pointers to submenu pages and action items.
            * Private to enforce validation through addItem().
            */
            std::vector<IMenuItem*> m_items {};

            /**
            * @brief Parent pointer.
            *
            * Keeps parent pointer to allow returning from submenu to a parent page
            */
            MenuPage* m_parent {};

        public:

            /**
            * @brief Parametric Menu Page constructor
            *
            * Creates a menu page item with given title and parent.
            */
           MenuPage(const std::string& title, MenuPage* parent = nullptr);

           /**
            * @brief Destroys the menu page and releases owned items.
            */
           ~MenuPage() override;


           /**
           * @brief Add an item to items vector
           *
           * @param item pointer to an item to append.
           */
           void addItem(IMenuItem* item);

           /**
           * @brief Returns the items vector
           *
           * @return Reference to the vector of contained menu items.
           */
           const std::vector<IMenuItem*>& getItems() const;

           /**
           * @brief Returns a singular item of items vector by index
           *
           *
           */
           IMenuItem* getItem(int index) const;

           /**
           * @brief Returns count of items in items vector
           *
           * @return count of items
           */
           int getCount() const;

           /**
           * @brief Returns parent pointer of item
           *
           * @return parent pointer
           */
           MenuPage* getParent() const;

           /**
           * @brief Enters this menu page when selected.
           *
           * Sets this page as the current menu in the navigator.
           *
           * @param navigator Pointer to the menu navigator.
           */
           void onSelect(MenuNavigator* navigator) override;

           /**
           * @brief Indicates whether this item represents a terminal menu entry.
           *
           * @return true if selecting this item does not lead to another menu,
           *         false if it leads to a submenu.
           */
           bool isEnd() const override;
    };
}
