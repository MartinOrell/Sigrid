#include "LogicTiles.h"

#include <ostream>

using namespace sigrid;

LogicTiles::LogicTiles(){}

void LogicTiles::init(const int& numColumns, const int& numRows, const std::vector<int>& repeatTileColorIds){

    std::vector<LogicTile> insertPattern;
    for(const auto& color: repeatTileColorIds){
        LogicTile newTile;
        newTile.setColor(color);
        insertPattern.push_back(std::move(newTile));
    }

    m_tiles.setInsertPattern(insertPattern);
    m_tiles.setSize(numColumns, numRows);
}

void LogicTiles::setHighlightColor(const Coord& coord, const int& colorId){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.setHighlightColor(colorId);
}

void LogicTiles::removeHighlight(const Coord& coord){

    auto tile_o = m_tiles.at(coord);
    if(tile_o == std::nullopt){
        return;
    }
    auto& tile = tile_o.value().get();

    tile.removeHighlight();
}

int LogicTiles::getNumColumns() const{
    return m_tiles.numColumns();
}

int LogicTiles::getNumRows() const{
    return m_tiles.numRows();
}

std::vector<int> LogicTiles::getRepeatColorIds() const{

    std::vector<int> repeatColorIds;

    for(auto& tile: m_tiles.getInsertPattern()){
        repeatColorIds.push_back(tile.getColorId());
    }

    return repeatColorIds;
}

bool LogicTiles::addColumnRight(){
    return m_tiles.addColumnRight();
}

bool LogicTiles::addColumnLeft(){
    return m_tiles.addColumnLeft();
}

bool LogicTiles::removeRightColumn(){
    return m_tiles.removeRightColumn();
}

bool LogicTiles::removeLeftColumn(){
    return m_tiles.removeLeftColumn();
}

bool LogicTiles::addRowUp(){
    return m_tiles.addRowUp();
}

bool LogicTiles::addRowDown(){
    return m_tiles.addRowDown();
}

bool LogicTiles::removeTopRow(){
    return m_tiles.removeTopRow();
}

bool LogicTiles::removeBottomRow(){
    return m_tiles.removeBottomRow();
}

void LogicTiles::clear(){
    m_tiles.clear();
}

std::optional<LogicTile> LogicTiles::getTile(const Coord& coord) const{
    return m_tiles.at(coord);
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicTiles &tiles)
{

    out << "Columns: " << tiles.m_tiles.numColumns() << "\n";
    out << "Rows: " << tiles.m_tiles.numRows() << "\n";
    out << "RepeatTileColors:";

    for(auto& tile: tiles.m_tiles.getInsertPattern()){
        out << " " << tile.getColorId();
    }

    return out;
}
