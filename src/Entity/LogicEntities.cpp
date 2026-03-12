#include "LogicEntities.h"

#include <iostream>

using namespace sigrid;

LogicEntities::LogicEntities(){}

void LogicEntities::removeEntity(const Coord& coord){
    m_pieces.erase(coord);
    m_circles.erase(coord);
}

void LogicEntities::moveEntity(const Coord& fromCoord, const Coord& toCoord){
    {
        auto it = m_pieces.find(fromCoord);
        if(it != m_pieces.end()){
            m_pieces.insert({toCoord, it->second});
            m_pieces.erase(fromCoord);
            return;
        }
    }
    {
        auto it = m_circles.find(fromCoord);
        if(it != m_circles.end()){
            m_circles.insert({toCoord, it->second});
            m_circles.erase(fromCoord);
            return;
        }
    }
}

void LogicEntities::addEntity(const Coord& coord, const LogicEntity& entity){
    if(std::holds_alternative<LogicPiece>(entity)){
        m_pieces.insert({coord, std::get<LogicPiece>(entity)});
    }
    else if(std::holds_alternative<LogicCircle>(entity)){
        m_circles.insert({coord, std::get<LogicCircle>(entity)});
    }
    else{
        std::cout << "LogicEntities: Unable to add Entity" << std::endl;
        std::cout << "Unknown index of variant: " << entity.index() << std::endl;
    }
}

void LogicEntities::clear(){
    m_pieces.clear();
    m_circles.clear();
}

bool LogicEntities::isEmptySquare(const Coord& coord) const{
    return m_pieces.find(coord) == m_pieces.end()
        && m_circles.find(coord) == m_circles.end();
}

std::optional<LogicEntity> LogicEntities::getEntityAt(const Coord& coord) const{

    {   
        auto it = m_pieces.find(coord);
        if(it != m_pieces.end()){
            return it->second;
        }
    }
    {   
        auto it = m_circles.find(coord);
        if(it != m_circles.end()){
            return it->second;
        }
    }
    return std::nullopt;
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicEntities &entities)
{
    for(const auto& piece: entities.m_pieces){
        out << "\nPiece: " << piece.second.getColorId()
            << " " << piece.second.getNotation()
            << " " << piece.first.getNotation();
    }
    for(const auto& circle: entities.m_circles){
        out << "\nCircle: " << circle.second.getColorId()
            << " " << circle.first.getNotation();
    }
    return out;
}
