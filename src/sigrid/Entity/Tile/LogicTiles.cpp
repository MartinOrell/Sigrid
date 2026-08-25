#include "sigrid/Entity/Tile/LogicTiles.h"

#include <ostream>

void sigrid::LogicTiles::setNumColumns(const int& numColumns){
    m_tiles.setNumColumns(numColumns);
}

void sigrid::LogicTiles::setNumRows(const int& numRows){
    m_tiles.setNumRows(numRows);
}

void sigrid::LogicTiles::setInsertPattern(const sigrid_list::Vector<int>& repeatTileColorIds){

    sigrid_list::Vector<LogicTile> insertPattern;
    for(const auto& color: repeatTileColorIds){
        LogicTile newTile;
        newTile.setColor(color);
        insertPattern.push_back(std::move(newTile));
    }

    m_tiles.setInsertPattern(insertPattern);
}

void sigrid::LogicTiles::insertAllTiles(){
    m_tiles.insertAllElements();
}

void sigrid::LogicTiles::setHighlightColor(const sigrid_coord::Coord& coord, const int& colorId){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.setHighlightColor(colorId);
}

void sigrid::LogicTiles::removeHighlight(const sigrid_coord::Coord& coord){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.removeHighlight();
}

int sigrid::LogicTiles::getNumColumns() const{
    return m_tiles.numColumns();
}

int sigrid::LogicTiles::getNumRows() const{
    return m_tiles.numRows();
}

sigrid_list::Vector<int> sigrid::LogicTiles::getRepeatColorIds() const{

    sigrid_list::Vector<int> repeatColorIds;

    for(auto& tile: m_tiles.getInsertPattern()){
        repeatColorIds.push_back(tile.getColorId());
    }

    return repeatColorIds;
}

bool sigrid::LogicTiles::addColumnRight(){
    return m_tiles.addColumnRight();
}

bool sigrid::LogicTiles::addColumnLeft(){
    return m_tiles.addColumnLeft();
}

bool sigrid::LogicTiles::removeRightColumn(){
    return m_tiles.removeRightColumn();
}

bool sigrid::LogicTiles::removeLeftColumn(){
    return m_tiles.removeLeftColumn();
}

bool sigrid::LogicTiles::addRowUp(){
    return m_tiles.addRowUp();
}

bool sigrid::LogicTiles::addRowDown(){
    return m_tiles.addRowDown();
}

bool sigrid::LogicTiles::removeTopRow(){
    return m_tiles.removeTopRow();
}

bool sigrid::LogicTiles::removeBottomRow(){
    return m_tiles.removeBottomRow();
}

void sigrid::LogicTiles::clear(){
    m_tiles.clear();
}

std::optional<sigrid::LogicTile> sigrid::LogicTiles::getTile(const sigrid_coord::Coord& coord) const{
    return m_tiles.at(coord);
}