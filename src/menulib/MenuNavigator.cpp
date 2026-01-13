#include "menulib/MenuNavigator.hpp"

namespace mr{
    MenuNavigator::MenuNavigator(MenuPage* root) : m_root(root), m_currentMenu(root), m_currentIndex(0){
        if(root == nullptr){
            throw std::invalid_argument("MenuNavigator: Root cannot be nullptr");
        }
    }

    const std::vector<IMenuItem*>& MenuNavigator::getCurrentItems() const{
       return m_currentMenu->getItems();
    }

    int MenuNavigator::getCurrentIndex() const{
        return m_currentIndex;
    }

    const std::string& MenuNavigator::getCurrentTitle() const{
        return m_currentMenu->getLabel();
    }

    void MenuNavigator::setCurrentMenu(MenuPage* currentMenu) {
        if(currentMenu == nullptr){
            throw std::invalid_argument("MenuNavigator: currentMenu cannot be nullptr");
        }
        m_currentMenu = currentMenu;

        m_currentIndex = 0;
    }

    void MenuNavigator::next(){
        int count = m_currentMenu->getCount();

        if (count == 0){
            return;
        }

        m_currentIndex++;

        // wrap around to the start if we exceed list size
        if(m_currentIndex >= count)
        {
            m_currentIndex = 0;
        }
    }

    void MenuNavigator::previous(){
        int count = m_currentMenu->getCount();

        if (count == 0){
            return;
        }

        m_currentIndex--;

        // wrap around to the end if we exceed list size
        if(m_currentIndex < 0)
        {
            m_currentIndex = count-1;
        }
    }

    void MenuNavigator::select() {
            if (!m_currentMenu){
                return;
            }

            const std::vector<IMenuItem*>& items = m_currentMenu->getItems();

            if (items.empty()) {
                return;
            }

            // We pass "this" (Navigator) to the item
            // If it's a Page it will use the navigator to enter the submenu
            // All other items will ignore the navigator and/or execute their function

            items[m_currentIndex]->onSelect(this);
    }

    void MenuNavigator::back() {
        if (m_currentMenu->getParent()) {
            m_currentIndex = 0;
            setCurrentMenu(m_currentMenu->getParent());
        }
    }

    MenuNavigator& MenuNavigator::operator++(){
        this->next();
        return *this;
    }

    MenuNavigator& MenuNavigator::operator--(){
        this->previous();
        return *this;
    }

    void MenuNavigator::operator()(){
        this->select();
    }

    void MenuNavigator::left(){
        if (!m_currentMenu){
            return;
        }

        const std::vector<IMenuItem*>& items = m_currentMenu->getItems();

        if (items.empty()) {
            return;
        }

        items[m_currentIndex]->onLeft(this);
    }

    void MenuNavigator::right(){
        if (!m_currentMenu){
            return;
        }

        const std::vector<IMenuItem*>& items = m_currentMenu->getItems();

        if (items.empty()) {
            return;
        }

        items[m_currentIndex]->onRight(this);
    }


}
