#include "Menu.h"

#include <SFML/Graphics/RenderTexture.hpp>
#include "MenuContainer.h"
#include "../Font/FontManager.h"
#include "MenuItem.h"

#include <iostream>

using namespace sigrid;


Menu::Menu()
: m_showHeaderIndex(-1)
, m_backgroundColor{255,255,255,0}{}

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

void Menu::createGraphic(const sf::Vector2u& size){

    if(size.x == 0){
        std::cerr << "Unable to create menu graphic with 0 width" << std::endl;
        return;
    }
    if(size.y == 0){
        std::cerr << "Unable to create menu graphic with 0 height" << std::endl;
        return;
    }

    m_texture = std::make_unique<sf::RenderTexture>(size);
    m_lineHeight = float(size.y);
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
    m_position = position;
}

bool Menu::contains(const sf::Vector2f& point) const{
    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains(point);
}

bool Menu::isPinned() const{
    return m_isPinned;
}

bool Menu::isCollapsed() const{
    return !m_showItems;
}

Action Menu::clicked(const sf::Vector2f& position){

    std::optional<sigrid::Menu::PosIndex> o_itemId = getMenuItemPosIndex(position);
    if(o_itemId == std::nullopt){
        if(m_showHeaderIndex != -1){
            m_showHeaderIndex = -1;
            redrawTexture();
        }
        return ActionType::None();
    }
    sigrid::Menu::PosIndex id = o_itemId.value();
    if(id.x == -1){
        if(!m_superHeaderPtr || m_isPinned){
            return ActionType::None();
        }
        return m_superHeaderPtr->getAction();
    }

    if(id.y > 0){
        m_showHeaderIndex = -1;
        redrawTexture();
    }

    return m_items.at(m_itemKeys.at(id.x).at(id.y))->getAction();
}

void Menu::pinMenu(){
    m_isPinned = !m_isPinned;
    redrawTexture();
}

bool Menu::showMenu(){

    assert(m_superHeaderPtr);

    if(!m_showItems || m_showHeaderIndex != -1){
        m_showItems = true;
    }
    else{
        m_showItems = false;
    }
    
    m_showHeaderIndex = -1;
    redrawTexture();

    return m_showItems;
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

    sigrid::ActionType::ShowMenu action;
    m_superHeaderPtr = std::make_unique<MenuItem>(name, *(fontPtr_o.value()), action);

    if(m_texture){
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

    auto newItem = std::make_unique<MenuItem>(name, *(fontPtr_o.value()), action);

    m_items.insert(std::pair{name, std::move(newItem)});

    std::vector<std::string> itemKeyList;
    itemKeyList.push_back(name);
    m_itemKeys.push_back(itemKeyList);

    LayoutItem layoutItem;
    layoutItem.headerIndex = id;
    layoutItem.priority = 0;
    m_layoutItems.insert(std::pair{name, layoutItem});

    if(m_texture){
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

    auto newItem = std::make_unique<MenuItem>(name, *(fontPtr_o.value()), action);

    m_items.insert(std::pair{name, std::move(newItem)});

    m_itemKeys.at(headerIndex).push_back(name);

    LayoutItem layoutItem;
    layoutItem.headerIndex = headerIndex;
    layoutItem.priority = m_layoutItems.size();
    m_layoutItems.insert(std::pair{name, layoutItem});

    if(m_texture){
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

    auto newItem = std::make_unique<MenuItem>(text0, *(fontPtr_o.value()), action0);

    newItem->addToggle(text1, action1);

    m_items.insert(std::pair{key, std::move(newItem)});

    m_itemKeys.at(headerIndex).push_back(key);

    LayoutItem layoutItem;
    layoutItem.headerIndex = headerIndex;
    layoutItem.priority = m_layoutItems.size();
    m_layoutItems.insert(std::pair{key, layoutItem});

    if(m_texture){
        unsigned int itemIndex = m_itemKeys.at(headerIndex).size()-1;
        addItemGraphic(headerIndex, itemIndex);
    }

}


void Menu::toggleItem(const std::string& key){

    auto it = m_items.find(key);
    if(it == m_items.end()){
        std::cerr << "Unable to toggle menu item. " << key << " not found" << std::endl;
        return;
    }

    it->second->toggle();

    redrawTexture();
}

void Menu::hideItem(const std::string& key){

    auto it = m_items.find(key);

    if(it == m_items.end()){
        std::cerr << "Unable to hide menu item. " << key << " not found" << std::endl;
        return;
    }

    for(int i = 0; i < m_itemKeys.size(); i++){
        for(auto it2 = m_itemKeys.at(i).begin(); it2 != m_itemKeys.at(i).end(); it2++){
            if(*it2 == it->first){
                m_itemKeys.at(i).erase(it2);
                return;
            }
        }
    }
}

void Menu::showItem(const std::string& key){

    auto it = m_items.find(key);

    if(it == m_items.end()){
        std::cerr << "Unable to show menu item. " << key << " not found" << std::endl;
        return;
    }

    if(m_itemKeys.at(m_layoutItems.at(key).headerIndex).size() == 0){
        m_itemKeys.at(m_layoutItems.at(key).headerIndex).push_back(it->first);
        return;
    }

    unsigned int priority = m_layoutItems.at(key).priority;
    for(auto it2 = m_itemKeys.at(m_layoutItems.at(key).headerIndex).begin(); it2 != m_itemKeys.at(m_layoutItems.at(key).headerIndex).end(); it2++){
        unsigned int cmpPriority = m_layoutItems.at(*it2).priority;
        if(priority > cmpPriority){
            if(it2+1 == m_itemKeys.at(m_layoutItems.at(key).headerIndex).end()){
                m_itemKeys.at(m_layoutItems.at(key).headerIndex).insert(it2, it->first);
                return;
            }
            unsigned int nextcmpPriority = m_layoutItems.at(*(it2+1)).priority;
            if(priority < nextcmpPriority){
                m_itemKeys.at(m_layoutItems.at(key).headerIndex).insert(it2, it->first);
                return;
            }
        }
    }
    std::cerr << "Menu: Unable to find position to show item " << key << std::endl;
}

void Menu::addSuperHeaderGraphic(){
    if(!m_texture){
        std::cerr << "Unable to add super header graphic, menu texture does not exist" << std::endl;
        return;
    }

    if(!m_superHeaderPtr){
        std::cerr << "Unable to add super header graphic, super header does not exist" << std::endl;
        return;
    }
    
    m_superHeaderPtr->createGraphic((unsigned int)m_lineHeight);
    float posX = m_itemOffsetX;
    float posY = m_lineHeight/2.f;
    m_superHeaderPtr->setPosition({posX, posY});
    m_texture->draw(*m_superHeaderPtr);
}

void Menu::addHeaderGraphic(const unsigned int id){

    if(m_lineHeight <= 0){
        std::cerr << "Menu: Height not set, unable to add header graphic" << std::endl;
        return;
    }

    m_items.at(m_itemKeys.at(id).at(0))->createGraphic((unsigned int)m_lineHeight);
    float posX;
    if(id == 0){
        if(m_isPinned){
            posX = m_itemOffsetX;
        }
        else{
            posX = m_superHeaderPtr->getPositionRight() + m_itemOffsetX;
        }
    }   
    else{
        posX = m_items.at(m_itemKeys.at(id-1).at(0))->getPositionRight() + m_itemOffsetX;
    }
    float posY = m_lineHeight/2.f;
    m_items.at(m_itemKeys.at(id).at(0))->setPosition({posX,posY});
    if(m_showItems){
        m_texture->draw(*m_items.at(m_itemKeys.at(id).at(0)));
    }
}

void Menu::addItemGraphic(const unsigned int headerIndex, const unsigned int itemIndex){

    int reverseItemIndex = m_itemKeys.at(headerIndex).size() - itemIndex;

    m_items.at(m_itemKeys.at(headerIndex).at(itemIndex))->createGraphic((unsigned int)m_lineHeight);
    float posX = m_items.at(m_itemKeys.at(headerIndex).at(0))->getPositionLeft();
    float posY = reverseItemIndex*m_lineHeight-m_lineHeight/2.f;
    m_items.at(m_itemKeys.at(headerIndex).at(itemIndex))->setPosition({posX, posY});
    if(m_showItems){
        m_texture->draw(*m_items.at(m_itemKeys.at(headerIndex).at(itemIndex)));
    }
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(!m_texture){
        return;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::RenderStates newStates{states};
    newStates.blendMode = sf::BlendAlpha;
    target.draw(sprite,newStates);
}

void sigrid::Menu::redrawTexture(){

    if(!m_texture){
        return;
    }

    unsigned int numRows;
    if(m_showHeaderIndex >= 0 && m_showHeaderIndex < m_itemKeys.size()){
        numRows = m_itemKeys.at(m_showHeaderIndex).size();
    }
    else{
        numRows = 1;
    }

    unsigned int textureSizeX = m_texture->getSize().x;
    unsigned int textureSizeY = (unsigned int)(m_lineHeight*(numRows));

    bool success = m_texture->resize({textureSizeX, textureSizeY});

    assert(success);

    m_texture->clear(m_backgroundColor);

    if(!m_isPinned && m_superHeaderPtr){
        float posX = m_superHeaderPtr->getPositionLeft();
        float posY = (float)textureSizeY - m_lineHeight/2.f;
        m_superHeaderPtr->setPosition({posX,posY});

        m_texture->draw(*m_superHeaderPtr);
    }

    if(!m_showItems){
        return;
    }

    for(int i = 0; i < m_itemKeys.size(); i++){
        float posX = m_items.at(m_itemKeys.at(i).at(0))->getPositionLeft();
        float posY = (float)textureSizeY - m_lineHeight/2.f;
        m_items.at(m_itemKeys.at(i).at(0))->setPosition({posX,posY});

        m_texture->draw(*m_items.at(m_itemKeys.at(i).at(0)));
    }

    if(m_showHeaderIndex == -1){
        return;
    }


    for(int i = 1; i < m_itemKeys.at(m_showHeaderIndex).size(); i++){
        m_texture->draw(*m_items.at(m_itemKeys.at(m_showHeaderIndex).at(i)));
    }
}

float sigrid::Menu::getTopPos(){
    return m_position.y;
}

float sigrid::Menu::getBottomPos(){
    if(!m_texture){
        return m_position.y;
    }
    return m_position.y+(float)m_texture->getSize().y;
}

std::optional<sigrid::Menu::PosIndex> Menu::getMenuItemPosIndex(const sf::Vector2f& point){
    if(m_superHeaderPtr && !m_isPinned && m_superHeaderPtr->isWithin(point, getTopPos(), getBottomPos())){
        sigrid::Menu::PosIndex id{-1,0};
        return id;
    }

    if(!m_showItems){
        return std::nullopt;
    }

    for(int i = 0; i < m_itemKeys.size(); i++){
        if(m_items.at(m_itemKeys.at(i).at(0))->isWithin(point, getTopPos(), getBottomPos())){
            sigrid::Menu::PosIndex id{i,0};
            return id;
        }
    }

    if(m_showHeaderIndex == -1){
        return std::nullopt;
    }

    assert(m_items.size()-1 >= m_showHeaderIndex);

    for(int i = 1; i < m_itemKeys.at(m_showHeaderIndex).size(); i++){
        if(m_items.at(m_itemKeys.at(m_showHeaderIndex).at(i))->isWithin(point, getTopPos(), getBottomPos())){
            sigrid::Menu::PosIndex id{m_showHeaderIndex,i};
            return id;
        }
    }

    return std::nullopt;
}