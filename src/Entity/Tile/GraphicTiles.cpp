#include "Entity/Tile/GraphicTiles.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include "Color/ColorManager.h"

#include <iostream>

using namespace sigrid;

GraphicTiles::GraphicTiles(){}

void GraphicTiles::setColorManagerPtr(ColorManager* const managerPtr){
    m_tileColorManagerPtr = managerPtr;
}

void GraphicTiles::setHighlightColorManagerPtr(ColorManager* const managerPtr){
    m_highlightColorManagerPtr = managerPtr;
}

void GraphicTiles::setNumColumns(const int& columns){
    m_tiles.setNumColumns(columns);
}

void GraphicTiles::setNumRows(const int& rows){
    m_tiles.setNumRows(rows);
}

void GraphicTiles::setTileSize(const sf::Vector2f& tileSize){

    m_tileSize = tileSize;

    if(m_tileSize.x <= 0.f){
        return;
    }
    if(m_tileSize.y <= 0.f){
        return;
    }

    GraphicTile tile;
    tile.setSize(m_tileSize);
    std::vector<GraphicTile> insertTiles;
    insertTiles.push_back(tile);
    m_tiles.setInsertPattern(insertTiles);
}

void GraphicTiles::setTopLeftPosition(const sf::Vector2f& topLeftPosition){
    m_topLeftPosition = topLeftPosition;
}

void GraphicTiles::init(const bool& isLeftToRight, const bool& isTopToBottom){

    unsigned int columns = m_tiles.numColumns();
    unsigned int rows = m_tiles.numRows();

    for(int y = 0; (unsigned int)y < rows; y++){
        for(int x = 0; (unsigned int)x < columns; x++){

            auto tile_o = m_tiles.at({x,y});
            if(tile_o == std::nullopt){
                continue;
            }
            auto& tile = tile_o.value().get();

            sf::Vector2f position = m_topLeftPosition;
            if(isLeftToRight){
                position.x += (float)(x*m_tileSize.x);
            }
            else{
                position.x += (float)((columns-x-1)*m_tileSize.x);
            }
            if(isTopToBottom){
                position.y += (float)(y*m_tileSize.y);
            }
            else{
                position.y += (float)((rows-y-1)*m_tileSize.y);
            }

            tile.setPosition(position);
        }
    }
}

void GraphicTiles::setTilePosition(const Coord& coord, const sf::Vector2f& position){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.setPosition(position);
}

void GraphicTiles::setTileColor(const Coord& coord, const int& colorId){
    
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

void GraphicTiles::setHighlightColor(const Coord& coord, const int& colorId){

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

void GraphicTiles::removeHighlight(const Coord& coord){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.removeHighlight();
}

void GraphicTiles::addColumnRight(const std::vector<int>& repeatTileColorIds, const bool& isLeftToRight){

    m_tiles.addColumnRight();

    int x = (int)m_tiles.numColumns()-1;
    for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){

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

        sf::Vector2f position = leftTile.getTopLeftPosition();
        if(isLeftToRight){
            position.x += m_tileSize.x;
        }

        sf::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color = sf::Color::White;
        }
        else{
            auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
            if(color_o == std::nullopt){
                color = sf::Color::White;
            }
            else{
                color = color_o.value();
            }
        }

        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }

    if(!isLeftToRight){
        for(int x = 0; (unsigned int)x < m_tiles.numColumns()-1; x++){
            for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){
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

void GraphicTiles::addColumnLeft(const std::vector<int>& repeatTileColorIds, const bool& isLeftToRight){

    m_tiles.addColumnLeft();

    int x = 0;
    for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){

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

        sf::Vector2f position = rightTile.getTopLeftPosition();
        if(isLeftToRight){
            position.x -= m_tileSize.x;
        }
        else{
            position.x += m_tileSize.x;
        }

        sf::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color = sf::Color::White;
        }
        else{
            auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
            if(color_o == std::nullopt){
                color = sf::Color::White;
            }
            else{
                color = color_o.value();
            }
        }

        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }

    if(isLeftToRight){
        for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
            for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){
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

void GraphicTiles::removeRightColumn(const bool& isLeftToRight){

    m_tiles.removeRightColumn();

    if(!isLeftToRight){
        for(int y=0; (unsigned int)y < m_tiles.numRows(); y++){
            for(int x=0; (unsigned int)x < m_tiles.numColumns(); x++){
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

void GraphicTiles::removeLeftColumn(const bool& isLeftToRight){

    m_tiles.removeLeftColumn();

    if(isLeftToRight){
        for(int y=0; (unsigned int)y < m_tiles.numRows(); y++){
            for(int x=0; (unsigned int)x < m_tiles.numColumns(); x++){
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

void GraphicTiles::addRowUp(const std::vector<int>& repeatTileColorIds, const bool& isTopToBottom){

    m_tiles.addRowUp();

    int y = 0;
    for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
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

        sf::Vector2f position = topTile.getTopLeftPosition();
        if(isTopToBottom){
            position.y -= m_tileSize.y;
        }
        else{
            position.y += m_tileSize.y;
        }

        sf::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color = sf::Color::White;
        }
        else{
            auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
            if(color_o == std::nullopt){
                color = sf::Color::White;
            }
            else{
                color = color_o.value();
            }
        }
        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }

    if(isTopToBottom){
        for(int y = (int)m_tiles.numRows()-1; y >= 0; y--){
            for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
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

void GraphicTiles::addRowDown(const std::vector<int>& repeatTileColorIds, const bool& isTopToBottom){

    m_tiles.addRowDown();

    int y = (int)m_tiles.numRows()-1;
    for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
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

        sf::Vector2f position = downTile.getTopLeftPosition();
        if(isTopToBottom){
            position.y += m_tileSize.y;
        }
        else{
            position.y -= m_tileSize.y;
        }

        sf::Color color;
        if(!m_tileColorManagerPtr || repeatTileColorIds.size() == 0){
           color = sf::Color::White;
        }
        else{
            auto color_o = m_tileColorManagerPtr->getSolidColor(repeatTileColorIds.at((x+y)%repeatTileColorIds.size()));
            if(color_o == std::nullopt){
                color = sf::Color::White;
            }
            else{
                color = color_o.value();
            }
        }

        currentTile.setPosition(position);
        currentTile.setTileColor(color);
    }

    if(!isTopToBottom){
        for(int y = (int)m_tiles.numRows()-1; y >= 0; y--){
            for(int x = 0; x < (unsigned int)m_tiles.numColumns(); x++){
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

void GraphicTiles::removeTopRow(const bool& isTopToBottom){

    m_tiles.removeTopRow();

    if(!isTopToBottom){
        for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){
            for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
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

void GraphicTiles::removeBottomRow(const bool& isTopToBottom){

    m_tiles.removeBottomRow();

    if(!isTopToBottom){
        for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){
            for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
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

void GraphicTiles::clear(){
    m_tiles.clear();
}

int GraphicTiles::getNumColumns() const{
    return m_tiles.numColumns();
}

int GraphicTiles::getNumRows() const{
    return m_tiles.numRows();
}

float GraphicTiles::getTileWidth() const{
    return m_tileSize.x;
}

float GraphicTiles::getTileHeight() const{
    return m_tileSize.y;
}

sf::Vector2f GraphicTiles::getTileSize() const{
    return m_tileSize;
}

std::optional<sf::Vector2f> GraphicTiles::getTileTopLeftPosition(const Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getTopLeftPosition();
}

std::optional<sf::Vector2f> GraphicTiles::getTileCentrePosition(const Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getCentrePosition();
}

std::optional<float> GraphicTiles::getTileRightPosition(const Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getRightPosition();
}

std::optional<float> GraphicTiles::getTileTopPosition(const Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getTopPosition();
}

std::optional<sf::Color> GraphicTiles::getTileColor(const Coord& coord) const{

    auto tile_o = m_tiles.at(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    auto& tile = tile_o.value().get();

    return tile.getColor();

}

void GraphicTiles::move(const sf::Vector2f& offset){

    for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){
        for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
            auto currentTile_o = m_tiles.at({x,y});
            if(currentTile_o == std::nullopt){
                continue;
            }
            auto& tile = currentTile_o.value().get();
            tile.move(offset);
        }
    }
}

void GraphicTiles::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(int y = 0; (unsigned int)y < m_tiles.numRows(); y++){
        for(int x = 0; (unsigned int)x < m_tiles.numColumns(); x++){
            auto currentTile_o = m_tiles.at({x,y});
            if(currentTile_o == std::nullopt){
                continue;
            }
            auto& tile = currentTile_o.value().get();
            target.draw(tile);
        }
    }
}