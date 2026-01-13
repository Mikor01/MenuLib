#pragma once
#include <string>

namespace mr{

    /**
    * @brief Forward declaration for menu navigation logic.
    */
    class MenuNavigator;


    /**
    * @brief Interface for all menu item types.
    *
    * IMenuItem is the base class for all menu entry types such as pages and action items
    * that can be displayed and selected by the user.
    */
    class IMenuItem{
        private:

            /**
            * @brief Display label of the menu item.
            */
            std::string m_label {};

        protected:

            /**
            * @brief Constructs a menu item with given label.
            *
            * Protected to prevent directly creating an interface instance without specified type.
            *
            * @param label text displayed for this menu item.
            */
            IMenuItem(const std::string& label) : m_label(label) {}

        public:

            /**
            * @brief Virtual destructor.
            */
            virtual ~IMenuItem() = default;

            /**
            * @brief Returns the menu item's display label.
            *
            * @return The menu item's label
            */
            virtual const std::string& getLabel() const
            {
                return m_label;
            }

            /**
            * @brief Indicates whether this item represents a terminal menu entry.
            *
            * @return true if selecting this item does not lead to another menu,
            *         false if it leads to a submenu.
            */
            virtual bool isEnd() const = 0;

            /**
            * @brief Called when the item is selected.
            *
            * Defines what happens when user selects this menu item
            * modifying the navigator state
            *
            * @param navigator Pointer to the menu navigator controlling the current menu.
            */
            virtual void onSelect(MenuNavigator* navigator) = 0;

            /**
            * @brief Sets the menu item's display label.
            *
            * @param label New label text
            */
            virtual void setLabel(const std::string& label)
            {
                if(!label.empty())
                {
                    m_label = label;
                }
            }

            /**
            * @brief Blank function for moving slider control to the left
            *
            * @param navigator Pointer to the menu navigator controlling the current menu.
            */
            virtual void onLeft(MenuNavigator* navigator){};

            /**
            * @brief Blank function for moving slider control to the right
            *
            * @param navigator Pointer to the menu navigator controlling the current menu.
            */
            virtual void onRight(MenuNavigator* navigator){};
    };
}
