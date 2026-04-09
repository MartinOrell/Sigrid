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

std::vector<int> LogicTiles::getRepeatColorIds() const{
    return m_repeatTileColorIds;
}

bool LogicTiles::addColumnRight(){
    if(m_repeatTileColorIds.size() == 0){
        return false;
    }

    m_columns++;
    int x = m_columns-1;
    for(int y = 0; y < m_rows; y++){
        LogicTile newTile{m_repeatTileColorIds.at((x+y)%m_repeatTileColorIds.size())};
        m_tiles.insert({{x,y},newTile});
    }
    return true;
}

bool LogicTiles::addColumnLeft(){
    if(m_repeatTileColorIds.size() == 0){
        return false;
    }
    int lastTileColorId = m_repeatTileColorIds.back();
    m_repeatTileColorIds.insert(m_repeatTileColorIds.begin(),lastTileColorId);
    m_repeatTileColorIds.pop_back();

    m_columns++;
    if(m_columns > 1){
        int x = m_columns-1;
        for(int y = 0; y < m_rows; y++){
            auto leftIt = m_tiles.find({x-1,y});
            if(leftIt != m_tiles.end()){
                LogicTile newTile = leftIt->second;
                m_tiles.insert({{x,y},newTile});
            }
        }
    }
    for(int x = m_columns-1; x > 0; x--){
        for(int y = 0; y < m_rows; y++){
            auto currentIt = m_tiles.find({x,y});
            auto leftIt = m_tiles.find({x-1,y});
            if(leftIt != m_tiles.end()){
                if(currentIt == m_tiles.end()){
                    LogicTile newTile = leftIt->second;
                    m_tiles.insert({{x,y},newTile});
                }
                else{
                    currentIt->second = leftIt->second;
                }
            }
            else{
                if(currentIt != m_tiles.end()){
                    m_tiles.erase(currentIt);
                }
            }
        }
    }
    {
        int x = 0;
        for(int y = 0; y < m_rows; y++){
            auto currentIt = m_tiles.find({x,y});
            if(currentIt == m_tiles.end()){
                LogicTile newTile{m_repeatTileColorIds.at((x+y)%m_repeatTileColorIds.size())};
                m_tiles.insert({{x,y},newTile});
            }
            else{
                currentIt->second = LogicTile{m_repeatTileColorIds.at((x+y)%m_repeatTileColorIds.size())};
            }
        }
    }

    return true;
}

bool LogicTiles::removeColumnRight(){
    if(m_columns <= 1){
        return false;
    }
    m_columns--;
    int x = m_columns;
    for(int y = 0; y < m_rows; y++){
        auto currentIt = m_tiles.find({x,y});
        if(currentIt != m_tiles.end()){
            m_tiles.erase(currentIt);
        }
    }
    return true;
}

bool LogicTiles::removeColumnLeft(){
    if(m_columns <= 1){
        return false;
    }

    int lastTileColorId = m_repeatTileColorIds.back();
    m_repeatTileColorIds.insert(m_repeatTileColorIds.begin(),lastTileColorId);
    m_repeatTileColorIds.pop_back();
    m_columns--;

    for(int x = m_columns-1; x >= 0; x--){
        for(int y = 0; y < m_rows; y++){
            auto currentIt = m_tiles.find({x,y});
            auto rightIt = m_tiles.find({x+1, y});
            if(rightIt != m_tiles.end()){
                if(currentIt == m_tiles.end()){
                    m_tiles.insert({{x,y}, rightIt->second});
                }
                else{
                    currentIt->second = rightIt->second;
                }
            }
            else{
                if(currentIt != m_tiles.end()){
                    m_tiles.erase(currentIt);
                }
            }
        }
    }
    {
        int x = m_columns;
        for(int y = 0; y < m_rows; y++){
            auto it = m_tiles.find({x,y});
            if(it != m_tiles.end()){
                m_tiles.erase(it);
            }
        }
    }
    return true;
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
