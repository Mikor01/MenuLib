#include "menulib/MenuPage.hpp"
#include "menulib/IMenuItem.hpp"
#include "menulib/MenuNavigator.hpp"

namespace mr{

    MenuPage::MenuPage(const std::string& label, MenuPage* parent) : IMenuItem(label), m_parent(parent){
        if(label.empty()){
            throw std::invalid_argument("MenuPage: Label cannot be empty");
        }
    }

    MenuPage::~MenuPage() {
        for (IMenuItem* item : m_items) {
            delete item;
        }
    }

    void MenuPage::addItem(IMenuItem* item){
        if (!item) {
            throw std::invalid_argument("MenuPage: Cannot add null item");
        }
        m_items.push_back(item);
    }

    const std::vector<IMenuItem*>& MenuPage::getItems() const {
        return m_items;
    }

    IMenuItem* MenuPage::getItem(int index) const{
        return m_items.at(index);
    }

    int MenuPage::getCount() const{
        return m_items.size();
    }

    MenuPage* MenuPage::getParent() const{
        return m_parent;
    }

    bool MenuPage::isEnd() const{
        return false;
    }

    void MenuPage::onSelect(MenuNavigator* navigator){
        navigator->setCurrentMenu(this);
    }

}
