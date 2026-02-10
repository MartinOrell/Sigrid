#include "Menu.h"

#include <iostream>

#include <SFML/Graphics/Sprite.hpp>

using namespace sigrid;


Menu::Menu(const GraphicBoardConfigContainer& gConfig, const MainWindowConfigContainer& wConfig)
: m_isPinned(wConfig.pinMenu)
, m_showItems(wConfig.pinMenu)
, m_showHeaderIndex(-1)
, m_backgroundColor{255,255,255,0}{

    bool loadFont = m_font.openFromFile("res/fonts/calibri.ttf");
    assert(loadFont);

    addSuperHeader("Menu");
    addHeader("File");
    addHeader("Edit");
    addHeader("View");
    addHeader("Settings");
    addHeader("Help");

    addItem("save image", 0, sigrid::ActionType::SaveBoardImage({"saveData/diagrams/images/board.png"}));
    addItem("Reset", 1, sigrid::ActionType::Reset{});
    addItem("Clear", 1, sigrid::ActionType::Clear{});
    
    addToggleItem("Coordinates", 1, "Add Coordinates", sigrid::ActionType::AddCoordinates{}, "Remove Coordinates", sigrid::ActionType::RemoveCoordinates{});
    addToggleItem("Move Coordinates", 1, "Move Coordinates Outside", sigrid::ActionType::MoveCoordinatesOutside{}, "Move Coordinates Inside", sigrid::ActionType::MoveCoordinatesInside{});
    addToggleItem("Set Coordinate Size", 1, "Set Big Coordinates", sigrid::ActionType::SetBigCoordinates{}, "Set Small Coordinates", sigrid::ActionType::SetSmallCoordinates{});

    if(gConfig.labelsInside){
        toggleItem("Coordinates");
        hideItem("Set Coordinate Size");
    }
    else if(gConfig.labelsOutside){
        toggleItem("Coordinates");
        toggleItem("Move Coordinates");
    }
    else{
        hideItem("Move Coordinates");
        hideItem("Set Coordinate Size");
    }
    addToggleItem("Toggle Border", 1, "Add Border", sigrid::ActionType::AddBoardBorder{}, "Remove Border", sigrid::ActionType::RemoveBoardBorder{});
    if(gConfig.border){
        toggleItem("Toggle Border");
    }
    
    addToggleItem("Toggle PlayerToMove Token", 1, "Add Player-to-move Token", sigrid::ActionType::AddPlayerToMoveToken{}, "Remove Player-to-move Token", sigrid::ActionType::RemovePlayerToMoveToken{});
    if(gConfig.playerToMoveToken){
        toggleItem("Toggle PlayerToMove Token");
    }
    
    addToggleItem("Pin Menu", 2, "Pin menu", sigrid::ActionType::PinMenu{}, "Unpin menu", sigrid::ActionType::PinMenu{});
    if(wConfig.pinMenu){
        toggleItem("Pin Menu");
    }
    
    addToggleItem("Tool Window", 2, "Show Tool Window", sigrid::ActionType::ShowTools{}, "Hide Tool Window", sigrid::ActionType::HideTools{});
    addToggleItem("Color Tools", 2, "Show Color Tools", sigrid::ActionType::ShowColorTools{}, "Hide Color Tools", sigrid::ActionType::HideColorTools{});

    if(wConfig.toolWindow){
        toggleItem("Tool Window");
    }
    else{
        hideItem("Color Tools");
    }
    
    if(wConfig.colorTools){
        toggleItem("Color Tools");
    }
    
    addItem("Print to console", 4, sigrid::ActionType::Print{});
}

void Menu::createGraphic(const sf::Vector2u& size){

    if(size.x == 0){
        std::cout << "Unable to create menu graphic with 0 width" << std::endl;
        return;
    }
    if(size.y == 0){
        std::cout << "Unable to create menu graphic with 0 height" << std::endl;
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

    reDrawTexture();
}

void Menu::setPosition(sf::Vector2f position){
    m_position = position;
}

bool Menu::contains(sf::Vector2i point) const{
    if(!m_texture){
        return false;
    }

    sf::Sprite sprite(m_texture->getTexture());
    sprite.setPosition(m_position);
    sf::FloatRect rect = sprite.getGlobalBounds();
    return rect.contains({(float)point.x, (float)point.y});
}

bool Menu::isPinned() const{
    return m_isPinned;
}

bool Menu::isCollapsed() const{
    return !m_showItems;
}

Action Menu::clicked(const sigrid::Tool& tool, const sf::Vector2i& position){

    std::optional<sigrid::Menu::PosIndex> o_itemId = getMenuItemPosIndex(position);
    if(o_itemId == std::nullopt){
        if(m_showHeaderIndex != -1){
            m_showHeaderIndex = -1;
            reDrawTexture();
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
        reDrawTexture();
    }

    return m_items.at(m_itemKeys.at(id.x).at(id.y))->getAction();
}

void Menu::pinMenu(){
    m_isPinned = !m_isPinned;
    reDrawTexture();
}

void Menu::showMenu(){

    assert(m_superHeaderPtr);

    if(!m_showItems || m_showHeaderIndex != -1){
        m_showItems = true;
    }
    else{
        m_showItems = false;
    }
    
    m_showHeaderIndex = -1;
    reDrawTexture();
}

void Menu::toggleHeader(const int headerId){

    if(m_showHeaderIndex != headerId){
        m_showHeaderIndex = headerId;
    }
    else{
        m_showHeaderIndex = -1;
    }
    reDrawTexture();
}

void Menu::addSuperHeader(const std::string& name){
    
    sigrid::ActionType::ShowMenu action;
    m_superHeaderPtr = std::make_unique<MenuItem>(name, m_font, action);

    if(m_texture){
        addSuperHeaderGraphic();
    }
}

void Menu::addHeader(const std::string& name){

    int id = m_items.size();
    sigrid::ActionType::ToggleHeader action{id};    

    auto newItem = std::make_unique<MenuItem>(name, m_font, action);

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

    assert(m_itemKeys.size()-1 >= headerIndex);
    assert(m_itemKeys.at(headerIndex).size() > 0);

    auto newItem = std::make_unique<MenuItem>(name, m_font, action);

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

    assert(m_itemKeys.size()-1 >= headerIndex);
    assert(m_itemKeys.at(headerIndex).size() > 0);

    auto newItem = std::make_unique<MenuItem>(text0, m_font, action0);

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
        std::cout << "Unable to toggle menu item. " << key << " not found" << std::endl;
        return;
    }

    it->second->toggle();

    reDrawTexture();
}

void Menu::hideItem(const std::string& key){

    auto it = m_items.find(key);

    if(it == m_items.end()){
        std::cout << "Unable to hide menu item. " << key << " not found" << std::endl;
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
        std::cout << "Unable to show menu item. " << key << " not found" << std::endl;
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
    std::cout << "Menu: Unable to find position to show item " << key << std::endl;
}

void Menu::addSuperHeaderGraphic(){
    if(!m_texture){
        std::cout << "Unable to add super header graphic, menu texture does not exist" << std::endl;
        return;
    }

    if(!m_superHeaderPtr){
        std::cout << "Unable to add super header graphic, super header does not exist" << std::endl;
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
        std::cout << "Height not set, unable to add header graphic" << std::endl;
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

    m_items.at(m_itemKeys.at(headerIndex).at(itemIndex))->createGraphic((unsigned int)m_lineHeight);
    float posX = m_items.at(m_itemKeys.at(headerIndex).at(0))->getPositionLeft();
    float posY = itemIndex*m_lineHeight-m_lineHeight/2.f;
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

void sigrid::Menu::reDrawTexture(){

    if(!m_texture){
        return;
    }

    unsigned int numRows;
    if(m_showHeaderIndex >= 0){
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

    if(!m_isPinned){
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

std::optional<sigrid::Menu::PosIndex> Menu::getMenuItemPosIndex(sf::Vector2i point){
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