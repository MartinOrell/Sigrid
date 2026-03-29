#include "GraphicTiles.h"

using namespace sigrid;

GraphicTiles::GraphicTiles(){}

void GraphicTiles::init(const int& columns, const int& rows, const sf::Vector2f& tileSize, ColorManager* const tileColorManagerPtr, ColorManager* const highlightColorManagerPtr, const sf::Vector2f& topLeftPosition, const bool& isLeftToRight, const bool& isTopToBottom){
    m_columns = columns;
    m_rows = rows;
    m_tileSize = tileSize;
    m_tileColorManagerPtr = tileColorManagerPtr;
    m_highlightColorManagerPtr = highlightColorManagerPtr;

    for(int y = 0; y < m_rows; y++){
        for(int x = 0; x < m_columns; x++){
            
            sf::Vector2f position;
            if(isLeftToRight){
                position.x = (float)(x*m_tileSize.x);
            }
            else{
                position.x = (float)((m_columns-x-1)*m_tileSize.x);
            }
            position.x += topLeftPosition.x;
            if(isTopToBottom){
                position.y = (float)(y*m_tileSize.y);
            }
            else{
                position.y = (float)((m_rows-y-1)*m_tileSize.y);
            }
            position.y += topLeftPosition.y;

            GraphicTile newTile;
            newTile.init(m_tileSize, sf::Color::White);
            newTile.setPosition(position);
            m_tiles.insert({{x,y}, newTile});
        }
    }
}

void GraphicTiles::setTilePosition(const Coord& coord, const sf::Vector2f& position){
    m_tiles.at(coord).setPosition(position);
}

void GraphicTiles::setTileColor(const Coord& coord, const int& colorId){
    
    auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);

    if(color_o != std::nullopt){
        m_tiles.at(coord).setTileColor(color_o.value());
    }
}

void GraphicTiles::setHighlightColor(const Coord& coord, const int& colorId){

    auto color_o = m_highlightColorManagerPtr->getTransparentColor(colorId);

    if(color_o != std::nullopt){
        m_tiles.at(coord).setHighlightColor(color_o.value());
    }
}

void GraphicTiles::removeHighlight(const Coord& coord){
    m_tiles.at(coord).removeHighlight();
}

int GraphicTiles::getNumColumns() const{
    return m_columns;
}

int GraphicTiles::getNumRows() const{
    return m_rows;
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

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getTopLeftPosition();
}

std::optional<sf::Vector2f> GraphicTiles::getTileCentrePosition(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getCentrePosition();
}

std::optional<float> GraphicTiles::getTileRightPosition(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getRightPosition();
}

std::optional<float> GraphicTiles::getTileTopPosition(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getTopPosition();
}

std::optional<sf::Color> GraphicTiles::getTileColor(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second.getColor();

}

void GraphicTiles::move(const sf::Vector2f& offset){
    for(auto& tile: m_tiles){
        tile.second.move(offset);
    }
}

void GraphicTiles::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(auto& tile: m_tiles){
        target.draw(tile.second);
    }
}