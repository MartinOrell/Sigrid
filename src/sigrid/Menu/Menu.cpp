#include "sigrid/Menu/Menu.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include "sigrid/Font/FontManager.h"

#include <iostream>

using namespace sigrid;

void Menu::setFontManagerPtr(FontManager* const managerPtr){
    m_fontManagerPtr = managerPtr;
}

bool Menu::load(const MenuContainer& menuData){
    m_isPinned = menuData.isPinned;
    m_showItems = menuData.showItems;
    m_fontFilename = menuData.fontName;

    addSuperHeader(menuData.title);
    for(const auto& header : menuData.headers){
        addHeader(header.name);
    }

    for(int i = 0; i < menuData.headers.size(); i++){

        const auto header_o = menuData.headers.at(i);
        if(header_o == std::nullopt){
            continue;
        }
        const auto& header = header_o.value().get();

        for(const auto& menuItem : header.items){
            if(menuItem.displayNames.size() == 1){

                auto actionName_o = menuItem.actionNames.at(0);
                if(actionName_o == std::nullopt){
                    return false;
                }
                const sigrid::String& actionName = actionName_o.value().get();

                auto action_o = sigrid_action::getAction(actionName);
                if(action_o == std::nullopt){
                    continue;
                }
                auto& action = action_o.value();

                auto displayName_o = menuItem.displayNames.at(0);
                if(displayName_o == std::nullopt){
                    return false;
                }
                sigrid::String displayName = displayName_o.value().get();

                addItem(std::move(displayName), i, action);
            }
            else if(menuItem.displayNames.size() == 2){

                auto actionAName_o = menuItem.actionNames.at(0);
                if(actionAName_o == std::nullopt){
                    return false;
                }
                const sigrid::String& actionAName = actionAName_o.value().get();

                auto actionA_o = sigrid_action::getAction(actionAName);
                if(actionA_o == std::nullopt){
                    return false;
                }

                auto actionBName_o = menuItem.actionNames.at(1);
                if(actionBName_o == std::nullopt){
                    return false;
                }
                const sigrid::String& actionBName = actionBName_o.value().get();

                auto actionB_o = sigrid_action::getAction(actionBName);
                if(actionB_o == std::nullopt){
                    return false;
                }
                auto& actionA = actionA_o.value();
                auto& actionB = actionB_o.value();

                auto activeDisplayName_o = menuItem.displayNames.at(0);
                if(activeDisplayName_o == std::nullopt){
                    return false;
                }

                auto inactiveDisplayName_o = menuItem.displayNames.at(1);
                if(inactiveDisplayName_o == std::nullopt){
                    return false;
                }

                addToggleItem(
                    menuItem.name,
                    i,
                    std::move(activeDisplayName_o.value().get()),
                    actionA,
                    std::move(inactiveDisplayName_o.value().get()),
                    actionB
                );
            }
            else{
                std::cerr << "Menu: Unable to handle menuItem with "
                    << menuItem.displayNames.size() << " states" << std::endl;
            }
        }
    
    }
    return true;
}

MenuContainer Menu::getContainer() const{
    
    MenuContainer menuContainer;
    menuContainer.isPinned = m_isPinned;
    menuContainer.fontName = m_fontFilename;
    menuContainer.title = m_superHeader.getName();

    for(const auto& header: m_itemKeys){
        HeaderContainer headerContainer;
        headerContainer.name = header.front();

        for(int i = 1; i < header.size(); ++i){

            sigrid::String itemKey = header.at(i);
            const auto item_o = m_items.at(itemKey);
            if(item_o == std::nullopt){
                std::cerr << "Menu: item at " << itemKey << " not found."
                    << " continue getting MenuContainer without that item." << std::endl;
                continue;
            }
            const MenuItem& item = item_o.value();
            MenuItemContainer itemContainer = item.getContainer();
            itemContainer.name = itemKey;

            headerContainer.items.push_back(std::move(itemContainer));
        }
        auto headerItems_o = m_items.at(header.front());

        menuContainer.headers.push_back(std::move(headerContainer));
    }

    return menuContainer;
}

void Menu::createGraphic(const sf::Vector2f& size){

    if(size.x == 0.f){
        std::cerr << "Menu: Unable to create menu graphic with 0 width" << std::endl;
        return;
    }
    if(size.y == 0.f){
        std::cerr << "Menu: Unable to create menu graphic with 0 height" << std::endl;
        return;
    }

    m_texture.setSize(size);
    m_lineHeight = size.y;
    m_itemOffsetX = 5.f;

    addSuperHeaderGraphic();

    for(int i = 0; i < m_itemKeys.size(); i++){
        addHeaderGraphic(i);
        for(int j = 1; j < m_itemKeys.at(i).size(); j++){
            addItemGraphic(i,j);
        }
    }

    redrawTexture();
}

void Menu::setPosition(const sf::Vector2f& position){
    m_texture.setPosition(position);
    m_texture.display();
}

bool Menu::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}

bool Menu::isPinned() const{
    return m_isPinned;
}

bool Menu::isCollapsed() const{
    return !m_showItems;
}

std::optional<sigrid_action::Action> Menu::clicked(const sf::Vector2f& position){

    std::optional<sigrid::Menu::PosIndex> itemId_o = getMenuItemPosIndex(position);
    if(itemId_o == std::nullopt){
        if(m_showHeaderIndex != -1){
            m_showHeaderIndex = -1;
            redrawTexture();
        }
        return std::nullopt;
    }
    sigrid::Menu::PosIndex id = itemId_o.value();
    if(id.x == -1){
        if(m_isPinned){
            return std::nullopt;
        }
        return m_superHeader.getAction();
    }

    if(id.y > 0){
        m_showHeaderIndex = -1;
        redrawTexture();
    }

    auto item_o = m_items.at(m_itemKeys.at(id.x).at(id.y));

    if(item_o == std::nullopt){
        return std::nullopt;
    }
    auto& item = item_o.value().get();

    return item.getAction();
}

void Menu::pinMenu(){
    m_isPinned = true;
    redrawTexture();
}

void Menu::unPinMenu(){
    m_isPinned = false;
    redrawTexture();
}

void Menu::showMenu(){

    m_showItems = true;
    m_showHeaderIndex = -1;
    m_superHeader.toggle();
    
    redrawTexture();
}

void Menu::hideMenu(){
    
    m_showItems = false;
    m_showHeaderIndex = -1;
    m_superHeader.toggle();

    redrawTexture();
}

void Menu::toggleHeader(const int headerId){

    if(m_showHeaderIndex != headerId){
        m_showHeaderIndex = headerId;
    }
    else{
        m_showHeaderIndex = -1;
    }
    redrawTexture();
}

void Menu::addSuperHeader(const sigrid::String& name){
    
    if(!m_fontManagerPtr){
        std::cerr << "Menu: Failed to add superHeader " << name << std::endl;
        std::cerr << "fontManager is nullptr" << std::endl;
        return;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);

    if(fontPtr_o == std::nullopt){
        std::cerr << "Menu: Failed to add superHeader " << name << std::endl;
        std::cerr << "font " << m_fontFilename << " not found" << std::endl;
        return;
    }

    sigrid_action::ShowMenu action0;
    sigrid_action::HideMenu action1;
    m_superHeader.setName(name);
    m_superHeader.setFont(*(fontPtr_o.value()));
    m_superHeader.setAction(action0);
    m_superHeader.addToggle(name, action1);

    if(m_texture.isInitialized()){
        addSuperHeaderGraphic();
    }
}

void Menu::addHeader(const sigrid::String& name){

    if(!m_fontManagerPtr){
        std::cerr << "Menu: Failed to add header " << name << std::endl;
        std::cerr << "fontManager is nullptr" << std::endl;
        return;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);

    if(fontPtr_o == std::nullopt){
        std::cerr << "Menu: Failed to add header " << name << std::endl;
        std::cerr << "font " << m_fontFilename << " not found" << std::endl;
        return;
    }

    int id = m_items.size();
    sigrid_action::ToggleHeader action{id};    

    MenuItem newItem;
    newItem.setName(name);
    newItem.setFont(*(fontPtr_o.value()));
    newItem.setAction(action);

    m_items.insert(name, std::move(newItem));

    std::vector<sigrid::String> itemKeyList;
    itemKeyList.push_back(name);
    m_itemKeys.push_back(itemKeyList);

    LayoutItem layoutItem;
    layoutItem.headerIndex = id;
    layoutItem.priority = 0;
    m_layoutItems.insert(name, std::move(layoutItem));

    if(m_texture.isInitialized()){
        addHeaderGraphic(id);
    }
}

void Menu::addItem(const sigrid::String& name, const int headerIndex, const sigrid_action::Action action){

    if(!m_fontManagerPtr){
        std::cerr << "Menu: Failed to add item " << name << std::endl;
        std::cerr << "fontManager is nullptr" << std::endl;
        return;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);

    if(fontPtr_o == std::nullopt){
        std::cerr << "Menu: Failed to menu item " << name << std::endl;
        std::cerr << "font " << m_fontFilename << " not found" << std::endl;
        return;
    }

    assert(m_itemKeys.size()-1 >= headerIndex);
    assert(m_itemKeys.at(headerIndex).size() > 0);

    MenuItem newItem;
    newItem.setName(name);
    newItem.setFont(*(fontPtr_o.value()));
    newItem.setAction(action);

    m_items.insert(name, std::move(newItem));

    m_itemKeys.at(headerIndex).push_back(name);

    LayoutItem layoutItem;
    layoutItem.headerIndex = headerIndex;
    layoutItem.priority = m_layoutItems.size();
    m_layoutItems.insert(name, std::move(layoutItem));

    if(m_texture.isInitialized()){
        int itemIndex = m_itemKeys.at(headerIndex).size()-1;
        addItemGraphic(headerIndex, itemIndex);
    }
}

void Menu::addToggleItem(const sigrid::String& key, const int headerIndex, const sigrid::String& text0, const sigrid_action::Action action0, const sigrid::String& text1, const sigrid_action::Action action1){

    if(!m_fontManagerPtr){
        std::cerr << "Menu: Failed to add toggle item " << key << std::endl;
        std::cerr << "fontManager is nullptr" << std::endl;
        return;
    }

    auto fontPtr_o = m_fontManagerPtr->getFontPtr(m_fontFilename);

    if(fontPtr_o == std::nullopt){
        std::cerr << "Menu: Failed to menu toggle item " << key << std::endl;
        std::cerr << "font " << m_fontFilename << " not found" << std::endl;
        return;
    }

    assert(m_itemKeys.size()-1 >= headerIndex);
    assert(m_itemKeys.at(headerIndex).size() > 0);

    MenuItem newItem;
    newItem.setName(text0);
    newItem.setFont(*(fontPtr_o.value()));
    newItem.setAction(action0);
    newItem.addToggle(text1, action1);

    m_items.insert(key, std::move(newItem));

    m_itemKeys.at(headerIndex).push_back(key);

    LayoutItem layoutItem;
    layoutItem.headerIndex = headerIndex;
    layoutItem.priority = m_layoutItems.size();
    m_layoutItems.insert(key, std::move(layoutItem));

    if(m_texture.isInitialized()){
        int itemIndex = m_itemKeys.at(headerIndex).size()-1;
        addItemGraphic(headerIndex, itemIndex);
    }

}


void Menu::toggleItem(const sigrid::String& key){

    auto item_o = m_items.at(key);

    if(item_o == std::nullopt){
        std::cerr << "Menu: Unable to toggle menu item. " << key << " not found" << std::endl;
        return;
    }
    auto& item = item_o.value().get();

    item.toggle();

    redrawTexture();
}

void Menu::hideItem(const sigrid::String& key){

    auto item_o = m_items.at(key);

    if(item_o == std::nullopt){
        std::cerr << "Menu: Unable to hide menu item. " << key << " not found" << std::endl;
        return;
    }

    for(int i = 0; i < m_itemKeys.size(); i++){
        for(auto it2 = m_itemKeys.at(i).begin(); it2 != m_itemKeys.at(i).end(); it2++){
            if(*it2 == key){
                m_itemKeys.at(i).erase(it2);
                return;
            }
        }
    }
}

void Menu::showItem(const sigrid::String& key){

    auto item_o = m_items.at(key);

    if(item_o == std::nullopt){
        std::cerr << "Menu: Unable to show menu item. " << key << " not found" << std::endl;
        return;
    }

    auto layoutItem_o = m_layoutItems.at(key);
    if(layoutItem_o == std::nullopt){
        return;
    }
    auto& layoutItem = layoutItem_o.value().get();

    if(m_itemKeys.at(layoutItem.headerIndex).size() == 0){
        m_itemKeys.at(layoutItem.headerIndex).push_back(key);
        return;
    }

    int priority = layoutItem.priority;
    for(auto it2 = m_itemKeys.at(layoutItem.headerIndex).begin(); it2 != m_itemKeys.at(layoutItem.headerIndex).end(); it2++){
        
        auto cmpLayoutItem_o = m_layoutItems.at(*it2);
        if(cmpLayoutItem_o == std::nullopt){
            continue;
        }
        auto& cmpLayoutItem = cmpLayoutItem_o.value().get();
        
        int cmpPriority = cmpLayoutItem.priority;
        if(priority > cmpPriority){
            if(it2+1 == m_itemKeys.at(layoutItem.headerIndex).end()){
                m_itemKeys.at(layoutItem.headerIndex).insert(it2, key);
                return;
            }

            auto nextCmpLayoutItem_o = m_layoutItems.at(*(it2+1));
            if(nextCmpLayoutItem_o == std::nullopt){
                continue;
            }
            auto& nextCmpLayoutItem = nextCmpLayoutItem_o.value().get();

            int nextcmpPriority = nextCmpLayoutItem.priority;
            if(priority < nextcmpPriority){
                m_itemKeys.at(layoutItem.headerIndex).insert(it2, key);
                return;
            }
        }
    }
    std::cerr << "Menu: Unable to find position to show item " << key << std::endl;
}

void Menu::addSuperHeaderGraphic(){

    if(!m_texture.isInitialized()){
        std::cerr << "Menu: Unable to add super header graphic, menu texture does not exist" << std::endl;
        return;
    }
    
    m_superHeader.createGraphic((int)m_lineHeight);
    float posX = m_itemOffsetX;
    float posY = m_lineHeight/2.f;
    m_superHeader.setPosition({posX, posY});
    redrawTexture();
}

void Menu::addHeaderGraphic(const int id){

    if(m_lineHeight <= 0){
        std::cerr << "Menu: Height not set, unable to add header graphic" << std::endl;
        return;
    }

    auto header_o = m_items.at(m_itemKeys.at(id).at(0));
    if(header_o == std::nullopt){
        std::cerr << "Menu: Unable to add header graphic. Header id "
            << id << " not found" << std::endl;
        return;
    }
    auto& header = header_o.value().get();

    header.createGraphic((int)m_lineHeight);
    float posX;
    if(id == 0){
        if(m_isPinned){
            posX = m_itemOffsetX;
        }
        else{
            posX = m_superHeader.getPositionRight() + m_itemOffsetX;
        }
    }   
    else{
        auto leftHeader_o = m_items.at(m_itemKeys.at(id-1).at(0));
        if(leftHeader_o != std::nullopt){
            auto& leftHeader = leftHeader_o.value().get();
            posX = leftHeader.getPositionRight() + m_itemOffsetX;
        }
    }
    float posY = m_lineHeight/2.f;
    header.setPosition({posX,posY});
    if(m_showItems){
        redrawTexture();
    }
}

void Menu::addItemGraphic(const int headerIndex, const int itemIndex){

    auto item_o = m_items.at(m_itemKeys.at(headerIndex).at(itemIndex));

    if(item_o == std::nullopt){
        std::cerr << "Menu: Unable to add item graphic. Item not found." << std::endl;
        return;
    }
    auto& item = item_o.value().get();

    auto header_o = m_items.at(m_itemKeys.at(headerIndex).at(0));
    if(header_o == std::nullopt){
        std::cerr << "Menu: Unable to add item graphic. Header not found." << std::endl;
        return;
    }
    auto& header = header_o.value().get();

    item.createGraphic((int)m_lineHeight);
    float posX = header.getPositionLeft();
    float posY = itemIndex*m_lineHeight+m_lineHeight/2.f;
    item.setPosition({posX, posY});
    if(m_showItems){
        redrawTexture();
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_texture);
}

void sigrid::Menu::redrawTexture(){

    if(!m_texture.isInitialized()){
        return;
    }

    int numRows;
    if(m_showHeaderIndex >= 0 && m_showHeaderIndex < m_itemKeys.size()){
        numRows = m_itemKeys.at(m_showHeaderIndex).size();
    }
    else{
        numRows = 1;
    }

    float textureSizeX = m_texture.getTextureSize().x;
    float textureSizeY = m_lineHeight*(float)numRows;

    m_texture.setSize(sf::Vector2f{textureSizeX, textureSizeY});

    m_texture.clear();

    if(!m_isPinned){
        m_texture.draw(m_superHeader);
    }

    if(!m_showItems){
        m_texture.display();
        return;
    }

    for(int i = 0; i < m_itemKeys.size(); i++){
        auto item_o = m_items.at(m_itemKeys.at(i).at(0));
        if(item_o == std::nullopt){
            std::cerr << "Menu: Missing header " << i << std::endl;
            continue;
        }
        auto& item = item_o.value().get();
        m_texture.draw(item);
    }

    if(m_showHeaderIndex == -1){
        m_texture.display();
        return;
    }

    for(int i = 1; i < m_itemKeys.at(m_showHeaderIndex).size(); i++){
        auto item_o = m_items.at(m_itemKeys.at(m_showHeaderIndex).at(i));
        if(item_o == std::nullopt){
            std::cerr << "Menu: Missing item "
                << m_showHeaderIndex << " " << i << std::endl;
            continue;
        }
        auto& item = item_o.value().get();
        m_texture.draw(item);
    }

    m_texture.display();
}

float sigrid::Menu::getTopPos(){
    return m_texture.getTopPosition();
}

float sigrid::Menu::getBottomPos(){
    return m_texture.getBottomPosition();
}

std::optional<sigrid::Menu::PosIndex> Menu::getMenuItemPosIndex(const sf::Vector2f& point){
    if(!m_isPinned && m_superHeader.isWithin(point, getTopPos(), getBottomPos())){
        sigrid::Menu::PosIndex id{-1,0};
        return id;
    }

    if(!m_showItems){
        return std::nullopt;
    }

    for(int i = 0; i < m_itemKeys.size(); i++){
        auto item_o = m_items.at(m_itemKeys.at(i).at(0));

        if(item_o == std::nullopt){
            return std::nullopt;
        }
        auto& item = item_o.value().get();

        if(item.isWithin(point, getTopPos(), getBottomPos())){
            sigrid::Menu::PosIndex id{i,0};
            return id;
        }
    }

    if(m_showHeaderIndex == -1){
        return std::nullopt;
    }

    for(int i = 1; i < m_itemKeys.at(m_showHeaderIndex).size(); i++){

        auto item_o = m_items.at(m_itemKeys.at(m_showHeaderIndex).at(i));

        if(item_o == std::nullopt){
            continue;
        }
        auto& item = item_o.value().get();

        if(item.isWithin(point, getTopPos(), getBottomPos())){
            sigrid::Menu::PosIndex id{m_showHeaderIndex,i};
            return id;
        }
    }

    return std::nullopt;
}