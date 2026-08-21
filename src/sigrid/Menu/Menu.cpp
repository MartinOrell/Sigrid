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

            if(!menuItem.isVisible){
                hideItem(menuItem.name);
            }
        }
    
    }
    return true;
}

std::optional<MenuContainer> Menu::getContainer() const{
    
    MenuContainer menuContainer;
    menuContainer.isPinned = m_isPinned;
    menuContainer.fontName = m_fontFilename;
    menuContainer.title = m_superHeader.getName();

    int nextPriority = m_itemKeys.numColumns()-1;
    for(int x = 0; x < m_itemKeys.numColumns(); ++x){

        HeaderContainer headerContainer;

        auto headerName_o = m_itemKeys.at({x,0});
        if(headerName_o == std::nullopt){
            std::cerr << "Menu: Failed to get headername " << x << "."
                << " Failed to get MenuContainer" << std::endl;
            return std::nullopt;
        }
        sigrid::String headerName = headerName_o.value();

        headerContainer.name = headerName;

        for(int y = 1; y < m_itemKeys.numRows(x); y++){

            ++nextPriority;
            auto itemKey_o = m_itemKeys.at({x,y});
            if(itemKey_o == std::nullopt){
                std::cerr << "Menu: Failed to get itemKey " << sigrid_coord::Coord{x,y}.getNotation() << "."
                    << " Failed to get MenuContainer" << std::endl;
                return std::nullopt;
            }
            sigrid::String itemKey = itemKey_o.value();
            const auto item_o = m_items.at(itemKey);
            if(item_o == std::nullopt){
                std::cerr << "Menu: item at " << itemKey << " not found."
                    << " continue getting MenuContainer without that item." << std::endl;
                continue;
            }
            const MenuItem& item = item_o.value();

            const auto layoutItem_o = m_layoutItems.at(itemKey);
            if(layoutItem_o == std::nullopt){
                std::cerr << "Menu: unable to find layout for " << itemKey << "."
                    << " continue getting MenuContainer without that item." << std::endl;
                continue;
            }
            const LayoutItem& layoutItem = layoutItem_o.value().get();

            //Add hidden items that are before the current item
            for(;nextPriority < layoutItem.priority; ++nextPriority){
                
                for(const auto& [lookupName, lookupItem]: m_items){
                    
                    const auto lookupLayout_o = m_layoutItems.at(lookupName);
                    if(lookupLayout_o == std::nullopt){
                        std::cerr << "Menu: unable to find layout for " << lookupName << "."
                            << " continue getting MenuContainer without that hidden item." << std::endl;
                        continue;
                    }
                    const auto& lookupLayout = lookupLayout_o.value().get();

                    if(lookupLayout.priority == nextPriority){

                        const auto hiddenItem_o = m_items.at(lookupName);
                        if(hiddenItem_o == std::nullopt){
                            std::cerr << "Menu: hidden item at " << lookupName << " not found."
                                << " continue getting MenuContainer without that hidden item." << std::endl;
                            break;
                        }
                        const MenuItem& hiddenItem = hiddenItem_o.value();

                        MenuItemContainer hiddenItemContainer = hiddenItem.getContainer();
                        hiddenItemContainer.name = lookupName;
                        hiddenItemContainer.isVisible = false;

                        headerContainer.items.push_back(std::move(hiddenItemContainer));
                        break;
                    }
                }
            }

            MenuItemContainer itemContainer = item.getContainer();
            itemContainer.name = itemKey;
            itemContainer.isVisible = true;

            headerContainer.items.push_back(std::move(itemContainer));
        }

        auto headerItems_o = m_items.at(headerName);

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

    for(int x = 0; x < m_itemKeys.numColumns(); ++x){
        addHeaderGraphic(x);
        for(int y = 1; y < m_itemKeys.numRows(x); ++y){
            addItemGraphic(x,y);
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

    std::optional<sigrid_coord::Coord> itemId_o = getMenuItemPosIndex(position);
    if(itemId_o == std::nullopt){
        if(m_showHeaderIndex != -1){
            m_showHeaderIndex = -1;
            redrawTexture();
        }
        return std::nullopt;
    }

    sigrid_coord::Coord id = itemId_o.value();
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

    auto itemKey_o = m_itemKeys.at(id);
    if(itemKey_o == std::nullopt){
        std::cerr << "Menu: Failed to get itemKey " << id.getNotation() << "."
            << " Failed to get action from click on Menu" << std::endl;
        return std::nullopt;
    }
    sigrid::String itemKey = itemKey_o.value();

    auto item_o = m_items.at(itemKey);

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

    {
        int x = m_itemKeys.numColumns();
        m_itemKeys.addColumn();
        m_itemKeys.push_back(x, name);
    }

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

    MenuItem newItem;
    newItem.setName(name);
    newItem.setFont(*(fontPtr_o.value()));
    newItem.setAction(action);

    m_items.insert(name, std::move(newItem));

    m_itemKeys.push_back(headerIndex, name);

    LayoutItem layoutItem;
    layoutItem.headerIndex = headerIndex;
    layoutItem.priority = m_layoutItems.size();
    m_layoutItems.insert(name, std::move(layoutItem));

    if(m_texture.isInitialized()){
        int itemIndex = m_itemKeys.numRows(headerIndex)-1;
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

    MenuItem newItem;
    newItem.setName(text0);
    newItem.setFont(*(fontPtr_o.value()));
    newItem.setAction(action0);
    newItem.addToggle(text1, action1);

    m_items.insert(key, std::move(newItem));

    m_itemKeys.push_back(headerIndex,key);

    LayoutItem layoutItem;
    layoutItem.headerIndex = headerIndex;
    layoutItem.priority = m_layoutItems.size();
    m_layoutItems.insert(key, std::move(layoutItem));

    if(m_texture.isInitialized()){
        int itemIndex = m_itemKeys.numRows(headerIndex)-1;
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

    for(int x = 0; x < m_itemKeys.numColumns(); ++x){
        for(int y = 1; y < m_itemKeys.numRows(x); ++y){
            
            auto itemKey_o = m_itemKeys.at({x,y});
            if(itemKey_o == std::nullopt){
                std::cerr << "Menu: Failed to get item key "
                    << sigrid_coord::Coord{x,y}.getNotation() << "."
                    << " Failed to hide item" << std::endl;
                continue;
            }
            sigrid::String& itemKey = itemKey_o.value().get();

            if(itemKey == key){
                m_itemKeys.erase({x,y});
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

    if(m_itemKeys.numRows(layoutItem.headerIndex) == 0){
        m_itemKeys.push_back(layoutItem.headerIndex, key);
        return;
    }

    int priority = layoutItem.priority;

    for(int y = 0; y < m_itemKeys.numRows(layoutItem.headerIndex); ++y){

        auto itemKey_o = m_itemKeys.at({layoutItem.headerIndex, y});
        if(itemKey_o == std::nullopt){
            std::cerr << "Menu: Failed to get item key "
                << sigrid_coord::Coord{layoutItem.headerIndex,y}.getNotation() << "."
                << " Failed to show item" << std::endl;
            continue;
        }
        sigrid::String& itemKey = itemKey_o.value().get();

        auto cmpLayoutItem_o = m_layoutItems.at(itemKey);
        if(cmpLayoutItem_o == std::nullopt){
            continue;
        }
        auto& cmpLayoutItem = cmpLayoutItem_o.value().get();
        
        int cmpPriority = cmpLayoutItem.priority;
        if(priority > cmpPriority){
            if(y+1 == m_itemKeys.numRows(layoutItem.headerIndex)){
                m_itemKeys.insert({layoutItem.headerIndex, y}, key);
                return;
            }

            auto nextItemKey_o = m_itemKeys.at({layoutItem.headerIndex, y+1});
            if(nextItemKey_o == std::nullopt){
                std::cerr << "Menu: Failed to get next item key "
                    << sigrid_coord::Coord{layoutItem.headerIndex,y+1}.getNotation() << "."
                    << " Failed to show item" << std::endl;
                continue;
            }
            sigrid::String& nextItemKey = nextItemKey_o.value().get();

            auto nextCmpLayoutItem_o = m_layoutItems.at(nextItemKey);
            if(nextCmpLayoutItem_o == std::nullopt){
                continue;
            }
            auto& nextCmpLayoutItem = nextCmpLayoutItem_o.value().get();

            int nextcmpPriority = nextCmpLayoutItem.priority;
            if(priority < nextcmpPriority){
                m_itemKeys.insert({layoutItem.headerIndex,y+1}, key);
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

    auto itemKey_o = m_itemKeys.at({id,0});
    if(itemKey_o == std::nullopt){

        std::cerr << "Menu: Failed to get item key "
            << sigrid_coord::Coord{id,0}.getNotation() << "."
            << " Failed to add headerGraphic" << std::endl;
        return;
    }
    sigrid::String itemKey = itemKey_o.value().get();

    auto header_o = m_items.at(itemKey);
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
        auto leftHeaderKey_o = m_itemKeys.at({id-1, 0});
        if(leftHeaderKey_o == std::nullopt){

            std::cerr << "Menu: Failed to get left header key "
                << sigrid_coord::Coord{id-1,0}.getNotation() << "."
                << " Failed to add headerGraphic" << std::endl;
            return;
        }
        sigrid::String& leftHeaderKey = leftHeaderKey_o.value().get();

        auto leftHeader_o = m_items.at(leftHeaderKey);
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

    auto itemKey_o = m_itemKeys.at({headerIndex, itemIndex});
    if(itemKey_o == std::nullopt){

        std::cerr << "Menu: Failed to get item key "
            << sigrid_coord::Coord{headerIndex,itemIndex}.getNotation() << "."
            << " Failed to add item graphic" << std::endl;
        return;
    }
    sigrid::String& itemKey = itemKey_o.value().get();

    auto item_o = m_items.at(itemKey);

    if(item_o == std::nullopt){
        std::cerr << "Menu: Unable to add item graphic. Item not found." << std::endl;
        return;
    }
    auto& item = item_o.value().get();

    auto headerKey_o = m_itemKeys.at({headerIndex, 0});
    if(headerKey_o == std::nullopt){

        std::cerr << "Menu: Failed to get header key "
            << sigrid_coord::Coord{headerIndex,0}.getNotation() << "."
            << " Failed to add item graphic" << std::endl;
        return;
    }
    sigrid::String& headerKey = headerKey_o.value().get();

    auto header_o = m_items.at(headerKey);
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
    if(m_showHeaderIndex >= 0 && m_showHeaderIndex < m_itemKeys.numColumns()){
        numRows = m_itemKeys.numRows(m_showHeaderIndex);
    }
    else{
        numRows = 1;
    }

    if(numRows <= 0){

        std::cerr << "Menu: Invalid number of item rows: " << numRows
            << " redraw Menu texture failed." << std::endl;
        return;
    }

    float textureSizeX = m_texture.getTextureSize().x;
    float textureSizeY = m_lineHeight*(float)numRows;

    if(textureSizeX <= 0.f){
        std::cerr << "Menu: texture width is " << textureSizeX
            << " which is an invalid width."
            << " redraw Menu texture failed." << std::endl;
        return;
    }

    if(textureSizeY <= 0.f){
        std::cerr << "Menu: texture height is " << textureSizeY
            << " which is an invalid height."
            << " redraw Menu texture failed." << std::endl;
        return;
    }

    m_texture.setSize(sf::Vector2f{textureSizeX, textureSizeY});

    m_texture.clear();

    if(!m_isPinned){
        m_texture.draw(m_superHeader);
    }

    if(!m_showItems){
        m_texture.display();
        return;
    }

    for(int i = 0; i < m_itemKeys.numColumns(); i++){

        auto itemKey_o = m_itemKeys.at({i,0});
        if(itemKey_o == std::nullopt){
            std::cerr << "Menu: Failed to get header key "
                << sigrid_coord::Coord{i,0}.getNotation() << "."
                << " Failed to redraw texture" << std::endl;
            continue;
        }
        sigrid::String& itemKey = itemKey_o.value().get();

        auto item_o = m_items.at(itemKey);
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

    for(int i = 1; i < m_itemKeys.numRows(m_showHeaderIndex); i++){

        auto itemKey_o = m_itemKeys.at({m_showHeaderIndex, i});
        if(itemKey_o == std::nullopt){

            std::cerr << "Menu: Failed to get item key "
                << sigrid_coord::Coord{m_showHeaderIndex,i}.getNotation() << "."
                << " Failed to redrawTexture" << std::endl;
            continue;
        }
        sigrid::String& itemKey = itemKey_o.value().get();

        auto item_o = m_items.at(itemKey);
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

std::optional<sigrid_coord::Coord> Menu::getMenuItemPosIndex(const sf::Vector2f& point){
    
    if(!m_isPinned && m_superHeader.isWithin(point, getTopPos(), getBottomPos())){
        sigrid_coord::Coord id{-1,0};
        return id;
    }

    if(!m_showItems){
        return std::nullopt;
    }

    for(int i = 0; i < m_itemKeys.numColumns(); i++){

        auto itemKey_o = m_itemKeys.at({i, 0});
        if(itemKey_o == std::nullopt){

            std::cerr << "Menu: Failed to get header key "
                << sigrid_coord::Coord{i,0}.getNotation() << "."
                << " Failed to get Menu Item Pos Index" << std::endl;
            continue;
        }
        sigrid::String& itemKey = itemKey_o.value().get();

        auto item_o = m_items.at(itemKey);

        if(item_o == std::nullopt){
            return std::nullopt;
        }
        auto& item = item_o.value().get();

        if(item.isWithin(point, getTopPos(), getBottomPos())){
            sigrid_coord::Coord id{i,0};
            return id;
        }
    }

    if(m_showHeaderIndex == -1){
        return std::nullopt;
    }

    for(int i = 1; i < m_itemKeys.numRows(m_showHeaderIndex); i++){

        auto itemKey_o = m_itemKeys.at({m_showHeaderIndex, i});
        if(itemKey_o == std::nullopt){
            std::cerr << "Menu: Failed to get item key "
                << sigrid_coord::Coord{m_showHeaderIndex,i}.getNotation() << "."
                << " Failed to get Menu Item Pos Index" << std::endl;
            continue;
        }
        sigrid::String& itemKey = itemKey_o.value().get();

        auto item_o = m_items.at(itemKey);

        if(item_o == std::nullopt){
            continue;
        }
        auto& item = item_o.value().get();

        if(item.isWithin(point, getTopPos(), getBottomPos())){
            sigrid_coord::Coord id{m_showHeaderIndex,i};
            return id;
        }
    }

    return std::nullopt;
}

void sigrid::Menu::printItemKeys() const{

    std::cout << "Item keys:" << std::endl;
    std::cout << "width: " << m_itemKeys.numColumns() << std::endl;
    for(int x = 0; x < m_itemKeys.numColumns(); ++x){
        
        std::cout << "height: " << m_itemKeys.numRows(x) << std::endl;
        std::cout << "[";
        for(int y = 0; y < m_itemKeys.numRows(x); ++y){
            
            auto itemKey_o = m_itemKeys.at({x,y});
            if(itemKey_o == std::nullopt){
                std::cout << " null";
                continue;
            }
            const sigrid::String& itemKey = itemKey_o.value().get();
            std::cout << " \"" << itemKey << "\"";
        }
        std::cout << " ]";
    }
    std::cout << std::endl;
}