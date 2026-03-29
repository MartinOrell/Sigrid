#include "GraphicTiles.h"

using namespace sigrid;

GraphicTiles::GraphicTiles(){}

void GraphicTiles::init(const int& columns, const int& rows, const sf::Vector2f& tileSize, ColorManager* const tileColorManagerPtr, ColorManager* const highlightColorManagerPtr){
    m_columns = columns;
    m_rows = rows;
    m_tileSize = tileSize;
    m_tileColorManagerPtr = tileColorManagerPtr;
    m_highlightColorManagerPtr = highlightColorManagerPtr;
}

void GraphicTiles::addTile(const Coord& coord, const sf::Vector2f& position, const int& colorId){

    if(!m_tileColorManagerPtr){
        return;
    }

    auto color_o = m_tileColorManagerPtr->getSolidColor(colorId);

    sf::Color color;
    if(color_o != std::nullopt){
        color = color_o.value();
    }

    GraphicTile newTile;
    newTile.init(m_tileSize, color);
    newTile.setPosition(position);
    m_tiles.insert({coord, newTile});
}

void GraphicTiles::setTilePosition(const Coord& coord, const sf::Vector2f& position){
    m_tiles.at(coord).setPosition(position);
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

sf::Vector2f GraphicTiles::getTileTopLeftPosition(const Coord& coord) const{
    return m_tiles.at(coord).getTopLeftPosition();
}

sf::Vector2f GraphicTiles::getTileCentrePosition(const Coord& coord) const{
    return m_tiles.at(coord).getCentrePosition();
}

float GraphicTiles::getTileRightPosition(const Coord& coord) const{
    return m_tiles.at(coord).getRightPosition();
}

float GraphicTiles::getTileTopPosition(const Coord& coord) const{
    return m_tiles.at(coord).getTopPosition();
}

std::optional<sf::Color> GraphicTiles::getTileColor(const Coord& coord) const{

    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return m_tiles.at(coord).getColor();

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