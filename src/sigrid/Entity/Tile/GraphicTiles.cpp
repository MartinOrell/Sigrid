#include "sigrid/Entity/Tile/GraphicTiles.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include "sigrid/Color/ColorManager.h"

#include <iostream>

sigrid::TileContainer sigrid::GraphicTiles::getTileContainer() const{

    TileContainer container;
    container.width = m_tileSize.x;
    container.height = m_tileSize.y;

    return container;
}

void sigrid::GraphicTiles::setColorManagerPtr(ColorManager* const managerPtr){
    m_tileColorManagerPtr = managerPtr;
}

void sigrid::GraphicTiles::setHighlightColorManagerPtr(ColorManager* const managerPtr){
    m_highlightColorManagerPtr = managerPtr;
}

void sigrid::GraphicTiles::setNumColumns(const int& columns){
    m_tiles.setNumColumns(columns);
}

void sigrid::GraphicTiles::setNumRows(const int& rows){
    m_tiles.setNumRows(rows);
}

void sigrid::GraphicTiles::setTileSize(const sigrid::Size_f& tileSize){

    m_tileSize = tileSize;

    GraphicTile tile;
    tile.setSize(m_tileSize);
    sigrid_list::Vector<GraphicTile> insertTiles;
    insertTiles.push_back(tile);
    m_tiles.setInsertPattern(insertTiles);
}

void sigrid::GraphicTiles::setTopLeftPosition(const sigrid::Position_f& topLeftPosition){
    m_topLeftPosition = topLeftPosition;
}

void sigrid::GraphicTiles::setLeftToRight(){
    m_isLeftToRight = true;
}

void sigrid::GraphicTiles::setRightToLeft(){
    m_isLeftToRight = false;
}

void sigrid::GraphicTiles::setTopToBottom(){
    m_isTopToBottom = true;
}

void sigrid::GraphicTiles::setBottomToTop(){
    m_isTopToBottom = false;
}

void sigrid::GraphicTiles::insertAllTiles(){

    int columns = m_tiles.numColumns();
    int rows = m_tiles.numRows();
    m_tiles.insertAllElements();

    for(int y = 0; y < rows; y++){
        for(int x = 0; x < columns; x++){

            auto tile_o = m_tiles.at({x,y});
            if(tile_o == std::nullopt){
                continue;
            }
            auto& tile = tile_o.value().get();

            sigrid::Position_f position = m_topLeftPosition;
            if(m_isLeftToRight){
                position.x += (float)(x*m_tileSize.x);
            }
            else{
                position.x += (float)((columns-x-1)*m_tileSize.x);
            }
            if(m_isTopToBottom){
                position.y += (float)(y*m_tileSize.y);
            }
            else{
                position.y += (float)((rows-y-1)*m_tileSize.y);
            }

            tile.setPosition(position);
        }
    }
}

void sigrid::GraphicTiles::setTilePosition(const sigrid_coord::Coord& coord, const sigrid::Position_f& position){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.setPosition(position);
}

void sigrid::GraphicTiles::setTileColor(const sigrid_coord::Coord& coord, const int& colorId){
    
    if(!m_tileColorManagerPtr){
        std::cerr << "GraphicTiles: Unable to set tile color" << std::endl;
        std::cerr << "TileColorManager is not set" << std::endl;
        return;
    }

    auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);

    if(color_o == std::nullopt){
        return;
    }

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.setTileColor(color_o.value());
}

void sigrid::GraphicTiles::setHighlightColor(const sigrid_coord::Coord& coord, const int& colorId){

    if(!m_highlightColorManagerPtr){
        std::cerr << "GraphicTiles: Unable to set highlight color" << std::endl;
        std::cerr << "Highlight ColorManager is not set" << std::endl;
        return;
    }

    auto color_o = m_highlightColorManagerPtr->getTransparentColor(colorId);

    if(color_o == std::nullopt){
        return;
    }

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.setHighlightColor(color_o.value());
}

void sigrid::GraphicTiles::removeHighlight(const sigrid_coord::Coord& coord){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.removeHighlight();
}

void sigrid::GraphicTiles::addColumnRight(const sigrid_list::Vector<int>& repeatTileColorIds){

    m_tiles.addColumnRight();

    int x = m_tiles.numColumns()-1;
    for(int y = 0; y < m_tiles.numRows(); y++){

        auto currentTile_o = m_tiles.at({x,y});
        if(currentTile_o == std::nullopt){
            continue;
        }

        auto leftTile_o = m_tiles.at({x-1,y});
        if(leftTile_o == std::nullopt){
            m_tiles.removeAt({x,y});
            continue;
        }

        auto& currentTile = currentTile_o.value().get();
        auto& leftTile = leftTile_o.value().get();

        sigrid::Position_f position = leftTile.getTopLeftPosition();
        if(m_isLeftToRight){
            position.x += m_tileSize.x;
        }

        sigrid::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color.setRGB(0xffffff);
        }
        else{
            auto colorId_o = repeatTileColorIds.at((x+y)%repeatTileColorIds.size());
            if(colorId_o == std::nullopt){
                color.setRGB(0xffffff);
            }
            else{
                const int& colorId = colorId_o.value().get();
                auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);
                if(color_o == std::nullopt){
                    color.setRGB(0xffffff);
                }
                else{
                    color = color_o.value();
                }
            }
        }

        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }

    if(!m_isLeftToRight){
        for(int x = 0; x < m_tiles.numColumns()-1; x++){
            for(int y = 0; y < m_tiles.numRows(); y++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();
                tile.move(sf::Vector2f{m_tileSize.x, 0.f});
            }
        }
    }
}

void sigrid::GraphicTiles::addColumnLeft(const sigrid_list::Vector<int>& repeatTileColorIds){

    m_tiles.addColumnLeft();

    int x = 0;
    for(int y = 0; y < m_tiles.numRows(); y++){

        auto currentTile_o = m_tiles.at({x,y});
        if(currentTile_o == std::nullopt){
            continue;
        }

        auto rightTile_o = m_tiles.at({x+1,y});
        if(rightTile_o == std::nullopt){
            m_tiles.removeAt({x,y});
            continue;
        }

        auto& currentTile = currentTile_o.value().get();
        auto& rightTile = rightTile_o.value().get();

        sigrid::Position_f position = rightTile.getTopLeftPosition();
        if(m_isLeftToRight){
            position.x -= m_tileSize.x;
        }
        else{
            position.x += m_tileSize.x;
        }

        sigrid::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color.setRGB(0xffffff);
        }
        else{
            auto colorId_o = repeatTileColorIds.at((x+y)%repeatTileColorIds.size());
            if(colorId_o == std::nullopt){
                color.setRGB(0xffffff);
            }
            else{
                const int& colorId = colorId_o.value().get();
                auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);
                if(color_o == std::nullopt){
                    color.setRGB(0xffffff);
                }
                else{
                    color = color_o.value();
                }
            }
        }

        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }

    if(m_isLeftToRight){
        for(int x = 0; x < m_tiles.numColumns(); x++){
            for(int y = 0; y < m_tiles.numRows(); y++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();
                tile.move(sf::Vector2f{m_tileSize.x, 0.f});
            }
        }
    }
}

void sigrid::GraphicTiles::removeRightColumn(){

    m_tiles.removeRightColumn();

    if(!m_isLeftToRight){
        for(int y=0; y < m_tiles.numRows(); y++){
            for(int x=0; x < m_tiles.numColumns(); x++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();
                tile.move(sf::Vector2f{-m_tileSize.x, 0.f});
            }
        }
    }
}

void sigrid::GraphicTiles::removeLeftColumn(){

    m_tiles.removeLeftColumn();

    if(m_isLeftToRight){
        for(int y=0; y < m_tiles.numRows(); y++){
            for(int x=0; x < m_tiles.numColumns(); x++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();
                tile.move(sf::Vector2f{-m_tileSize.x, 0.f});
            }
        }
    }
}

void sigrid::GraphicTiles::addRowUp(const sigrid_list::Vector<int>& repeatTileColorIds){

    m_tiles.addRowUp();

    int y = 0;
    for(int x = 0; x < m_tiles.numColumns(); x++){
        auto currentTile_o = m_tiles.at({x,y});
        if(currentTile_o == std::nullopt){
            continue;
        }

        auto topTile_o = m_tiles.at({x,y+1});
        if(topTile_o == std::nullopt){
            m_tiles.removeAt({x,y});
            continue;
        }

        auto& currentTile = currentTile_o.value().get();
        auto& topTile = topTile_o.value().get();

        sigrid::Position_f position = topTile.getTopLeftPosition();
        if(m_isTopToBottom){
            position.y -= m_tileSize.y;
        }
        else{
            position.y += m_tileSize.y;
        }

        sigrid::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color.setRGB(0xffffff);
        }
        else{
            auto colorId_o = repeatTileColorIds.at((x+y)%repeatTileColorIds.size());
            if(colorId_o == std::nullopt){
                color.setRGB(0xffffff);
            }
            else{
                const int& colorId = colorId_o.value().get();
                auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);
                if(color_o == std::nullopt){
                    color.setRGB(0xffffff);
                }
                else{
                    color = color_o.value();
                }
            }
        }
        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }

    if(m_isTopToBottom){
        for(int y = (int)m_tiles.numRows()-1; y >= 0; y--){
            for(int x = 0; x < m_tiles.numColumns(); x++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();
                tile.move(sf::Vector2f{0.f, m_tileSize.y});
            }
        }
    }
}

void sigrid::GraphicTiles::addRowDown(const sigrid_list::Vector<int>& repeatTileColorIds){

    m_tiles.addRowDown();

    int y = (int)m_tiles.numRows()-1;
    for(int x = 0; x < m_tiles.numColumns(); x++){
        auto currentTile_o = m_tiles.at({x,y});
        if(currentTile_o == std::nullopt){
            continue;
        }

        auto downTile_o = m_tiles.at({x,y-1});
        if(downTile_o == std::nullopt){
            m_tiles.removeAt({x,y});
            continue;
        }

        auto& currentTile = currentTile_o.value().get();
        auto& downTile = downTile_o.value().get();

        sigrid::Position_f position = downTile.getTopLeftPosition();
        if(m_isTopToBottom){
            position.y += m_tileSize.y;
        }
        else{
            position.y -= m_tileSize.y;
        }

        sigrid::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color.setRGB(0xffffff);
        }
        else{
            auto colorId_o = repeatTileColorIds.at((x+y)%repeatTileColorIds.size());
            if(colorId_o == std::nullopt){
                color.setRGB(0xffffff);
            }
            else{
                const int& colorId = colorId_o.value().get();
                auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);
                if(color_o == std::nullopt){
                    color.setRGB(0xffffff);
                }
                else{
                    color = color_o.value();
                }
            }
        }

        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }
    if(!m_isTopToBottom){
        for(int y = m_tiles.numRows()-1; y >= 0; y--){
            for(int x = 0; x < m_tiles.numColumns(); x++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();

                tile.move(sf::Vector2f{0.f, m_tileSize.y});
            }
        }
    }
}

void sigrid::GraphicTiles::removeTopRow(){

    m_tiles.removeTopRow();

    if(m_isTopToBottom){
        for(int y = 0; y < m_tiles.numRows(); y++){
            for(int x = 0; x < m_tiles.numColumns(); x++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();
                tile.move(sf::Vector2f{0.f, -m_tileSize.y});
            }
        }
    }
}

void sigrid::GraphicTiles::removeBottomRow(){

    m_tiles.removeBottomRow();

    if(!m_isTopToBottom){
        for(int y = 0; y < m_tiles.numRows(); y++){
            for(int x = 0; x < m_tiles.numColumns(); x++){
                auto currentTile_o = m_tiles.at({x,y});
                if(currentTile_o == std::nullopt){
                    continue;
                }
                auto& tile = currentTile_o.value().get();
                tile.move(sf::Vector2f{0.f, -m_tileSize.y});
            }
        }
    }
}

void sigrid::GraphicTiles::clear(){
    m_tiles.clear();
}

int sigrid::GraphicTiles::getNumColumns() const{
    return m_tiles.numColumns();
}

int sigrid::GraphicTiles::getNumRows() const{
    return m_tiles.numRows();
}

float sigrid::GraphicTiles::getTileWidth() const{
    return m_tileSize.x;
}

float sigrid::GraphicTiles::getTileHeight() const{
    return m_tileSize.y;
}

sigrid::Position_f sigrid::GraphicTiles::getTileSize() const{
    return m_tileSize;
}

std::optional<sigrid::Position_f> sigrid::GraphicTiles::getTileTopLeftPosition(const sigrid_coord::Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getTopLeftPosition();
}

std::optional<sigrid::Position_f> sigrid::GraphicTiles::getTileCentrePosition(const sigrid_coord::Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getCentrePosition();
}

std::optional<float> sigrid::GraphicTiles::getTileRightPosition(const sigrid_coord::Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getRightPosition();
}

std::optional<float> sigrid::GraphicTiles::getTileTopPosition(const sigrid_coord::Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getTopPosition();
}

std::optional<sigrid::Color> sigrid::GraphicTiles::getTileColor(const sigrid_coord::Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getColor();
}

float sigrid::GraphicTiles::getRightPosition() const{

    float x = m_topLeftPosition.x;
    x+= m_tileSize.x * (float)m_tiles.numColumns();
    return x;
}

void sigrid::GraphicTiles::move(const sf::Vector2f& offset){

    for(int y = 0; y < m_tiles.numRows(); y++){
        for(int x = 0; x < m_tiles.numColumns(); x++){
            auto currentTile_o = m_tiles.at({x,y});
            if(currentTile_o == std::nullopt){
                continue;
            }
            auto& tile = currentTile_o.value().get();
            tile.move(offset);
        }
    }
}

void sigrid::GraphicTiles::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(int y = 0; y < m_tiles.numRows(); y++){
        for(int x = 0; x < m_tiles.numColumns(); x++){
            auto currentTile_o = m_tiles.at({x,y});
            if(currentTile_o == std::nullopt){
                continue;
            }
            auto& tile = currentTile_o.value().get();
            target.draw(tile);
        }
    }
}