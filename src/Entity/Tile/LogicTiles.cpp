#include "LogicTiles.h"

#include <iostream>

using namespace sigrid;

LogicTiles::LogicTiles(){}

void LogicTiles::init(const int& numColumns, const int& numRows, const std::vector<int>& repeatTileColorIds){

    m_columns = numColumns;
    m_rows = numRows;
    m_repeatTileColorIds = repeatTileColorIds;

    for(int y = 0; y < numRows; y++){
        for(int x = 0; x < numColumns; x++){
            m_tiles.insert({Coord{x,y}, LogicTile{m_repeatTileColorIds.at((x+y)%m_repeatTileColorIds.size())}});
        }
    }
}

void LogicTiles::setHighlightColor(const Coord& coord, const int& colorId){
    m_tiles.at(coord).setHighlightColor(colorId);
}

void LogicTiles::removeHighlight(const Coord& coord){
    m_tiles.at(coord).removeHighlight();
}

int LogicTiles::getNumColumns() const{
    return m_columns;
}

int LogicTiles::getNumRows() const{
    return m_rows;
}

std::optional<LogicTile> LogicTiles::getTile(const Coord& coord) const{
    
    auto it = m_tiles.find(coord);

    if(it == m_tiles.end()){
        return std::nullopt;
    }

    return it->second;
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicTiles &tiles)
{

    out << "Columns: " << tiles.m_columns << "\n";
    out << "Rows: " << tiles.m_rows << "\n";
    out << "RepeatTileColors:";
    for(const auto& id: tiles.m_repeatTileColorIds){
        out << " " << id;
    }

    return out;
}
