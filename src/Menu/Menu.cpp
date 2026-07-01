#include "Menu.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include "MenuContainer.h"
#include "../Font/FontManager.h"

#include <iostream>

using namespace sigrid;


Menu::Menu()
: m_showHeaderIndex(-1){}

void Menu::setFontManagerPtr(FontManager* const managerPtr){
    m_fontManagerPtr = managerPtr;
}

void Menu::init(const MenuContainer& menuData){
    m_isPinned = menuData.isPinned;
    m_showItems = menuData.showItems;
    m_fontFilename = menuData.fontName;

    addSuperHeader(menuData.title);
    for(const auto& headerName : menuData.headerNames){
        addHeader(headerName);
    }

    for(const auto& menuItem : menuData.menuItems){
        if(menuItem.displayNames.size() == 1){
            addItem(menuItem.displayNames.at(0), menuItem.headerId, getAction(menuItem.actionNames.at(0)));
        }
        else if(menuItem.displayNames.size() == 2){
            addToggleItem(
                menuItem.keyName,
                menuItem.headerId,
                menuItem.displayNames.at(0),
                getAction(menuItem.actionNames.at(0)),
                menuItem.displayNames.at(1),
                getAction(menuItem.actionNames.at(1))
            );
        }
        else{
            std::cerr << "Menu: Unable to handle menuItem with "
                << menuItem.displayNames.size() << " states" << std::endl;
        }
    }
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

Action Menu::clicked(const sf::Vector2f& position){

    std::optional<sigrid::Menu::PosIndex> itemId_o = getMenuItemPosIndex(position);
    if(itemId_o == std::nullopt){
        if(m_showHeaderIndex != -1){
            m_showHeaderIndex = -1;
            redrawTexture();
        }
        return ActionType::None();
    }
    sigrid::Menu::PosIndex id = itemId_o.value();
    if(id.x == -1){
        if(m_isPinned){
            return ActionType::None();
        }
        return m_superHeader.getAction();
    }

    if(id.y > 0){
        m_showHeaderIndex = -1;
        redrawTexture();
    }

    auto item_o = m_items.at(m_itemKeys.at(id.x).at(id.y));

    if(item_o == std::nullopt){
        return ActionType::None();
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

void Menu::addSuperHeader(const std::string& name){
    
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

    sigrid::ActionType::ShowMenu action0;
    sigrid::ActionType::HideMenu action1;
    m_superHeader.setName(name);
    m_superHeader.setFont(*(fontPtr_o.value()));
    m_superHeader.setAction(action0);
    m_superHeader.addToggle(name, action1);

    if(m_texture.isInitialized()){
        addSuperHeaderGraphic();
    }
}

void Menu::addHeader(const std::string& name){

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
    sigrid::ActionType::ToggleHeader action{id};    

    MenuItem newItem;
    newItem.setName(name);
    newItem.setFont(*(fontPtr_o.value()));
    newItem.setAction(action);

    m_items.insert(name, std::move(newItem));

    std::vector<std::string> itemKeyList;
    itemKeyList.push_back(name);
    m_itemKeys.push_back(itemKeyList);

    LayoutItem layoutItem;
    layoutItem.headerIndex = id;
    layoutItem.priority = 0;
    m_layoutItems.insert(std::pair{name, layoutItem});

    if(m_texture.isInitialized()){
        addHeaderGraphic(id);
    }
}

void Menu::addItem(const std::string& name, const int headerIndex, const Action action){

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
    m_layoutItems.insert(std::pair{name, layoutItem});

    if(m_texture.isInitialized()){
        unsigned int itemIndex = m_itemKeys.at(headerIndex).size()-1;
        addItemGraphic(headerIndex, itemIndex);
    }
}

void Menu::addToggleItem(const std::string& key, const int headerIndex, const std::string& text0, const Action action0, const std::string& text1, const Action action1){

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
    m_layoutItems.insert(std::pair{key, layoutItem});

    if(m_texture.isInitialized()){
        unsigned int itemIndex = m_itemKeys.at(headerIndex).size()-1;
        addItemGraphic(headerIndex, itemIndex);
    }

}


void Menu::toggleItem(const std::string& key){

    auto item_o = m_items.at(key);

    if(item_o == std::nullopt){
        std::cerr << "Menu: Unable to toggle menu item. " << key << " not found" << std::endl;
        return;
    }
    auto& item = item_o.value().get();

    item.toggle();

    redrawTexture();
}

void Menu::hideItem(const std::string& key){

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

void Menu::showItem(const std::string& key){

    auto item_o = m_items.at(key);

    if(item_o == std::nullopt){
        std::cerr << "Menu: Unable to show menu item. " << key << " not found" << std::endl;
        return;
    }

    if(m_itemKeys.at(m_layoutItems.at(key).headerIndex).size() == 0){
        m_itemKeys.at(m_layoutItems.at(key).headerIndex).push_back(key);
        return;
    }

    unsigned int priority = m_layoutItems.at(key).priority;
    for(auto it2 = m_itemKeys.at(m_layoutItems.at(key).headerIndex).begin(); it2 != m_itemKeys.at(m_layoutItems.at(key).headerIndex).end(); it2++){
        unsigned int cmpPriority = m_layoutItems.at(*it2).priority;
        if(priority > cmpPriority){
            if(it2+1 == m_itemKeys.at(m_layoutItems.at(key).headerIndex).end()){
                m_itemKeys.at(m_layoutItems.at(key).headerIndex).insert(it2, key);
                return;
            }
            unsigned int nextcmpPriority = m_layoutItems.at(*(it2+1)).priority;
            if(priority < nextcmpPriority){
                m_itemKeys.at(m_layoutItems.at(key).headerIndex).insert(it2, key);
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
    
    m_superHeader.createGraphic((unsigned int)m_lineHeight);
    float posX = m_itemOffsetX;
    float posY = m_lineHeight/2.f;
    m_superHeader.setPosition({posX, posY});
    redrawTexture();
}

void Menu::addHeaderGraphic(const unsigned int id){

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

    header.createGraphic((unsigned int)m_lineHeight);
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

void Menu::addItemGraphic(const unsigned int headerIndex, const unsigned int itemIndex){

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

    item.createGraphic((unsigned int)m_lineHeight);
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

    unsigned int numRows;
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