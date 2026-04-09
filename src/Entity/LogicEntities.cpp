#include "LogicEntities.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace sigrid;

LogicEntities::LogicEntities(){}

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

void LogicEntities::clear(){
    m_pieces.clear();
    m_circles.clear();
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

void LogicEntities::removeColumn(const int& columnId){
    for(auto it = m_pieces.begin(); it != m_pieces.end();){
        if(it->first.x == columnId){
            it = m_pieces.erase(it);
        }
        else{
            it++;
        }
    }

    for(auto it = m_circles.begin(); it != m_circles.end();){
        if(it->first.x == columnId){
            it = m_circles.erase(it);
        }
        else{
            it++;
        }
    }
}

void LogicEntities::moveEntitiesRight(){

    if(m_pieces.size() > 0){
        int minX = 2147483647;
        int maxX = 0;
        int minY = 2147483647;
        int maxY = 0;

        for(auto& piece: m_pieces){
            if(piece.first.x < minX){
                minX = piece.first.x;
            }
            if(piece.first.x > maxX){
                maxX = piece.first.x;
            }
            if(piece.first.y < minY){
                minY = piece.first.y;
            }
            if(piece.first.y > maxY){
                maxY = piece.first.y;
            }
        }

        for(int x = maxX; x >= minX; x--){
            for(int y = minY; y <= maxY; y++){
                auto it = m_pieces.find({x,y});
                if(it != m_pieces.end()){
                    m_pieces.insert({{x+1,y},it->second});
                    m_pieces.erase(it);
                }
            }
        }
    }

    if(m_circles.size() > 0){
        int minX = 2147483647;
        int maxX = 0;
        int minY = 2147483647;
        int maxY = 0;

        for(auto& circle: m_circles){
            if(circle.first.x < minX){
                minX = circle.first.x;
            }
            if(circle.first.x > maxX){
                maxX = circle.first.x;
            }
            if(circle.first.y < minY){
                minY = circle.first.y;
            }
            if(circle.first.y > maxY){
                maxY = circle.first.y;
            }
        }

        for(int x = maxX; x >= minX; x--){
            for(int y = minY; y <= maxY; y++){
                auto it = m_circles.find({x,y});
                if(it != m_circles.end()){
                    m_circles.insert({{x+1,y},it->second});
                    m_circles.erase(it);
                }
            }
        }
    }
}

void LogicEntities::moveEntitiesLeft(){

    if(m_pieces.size() > 0){
        int minX = 2147483647;
        int maxX = 0;
        int minY = 2147483647;
        int maxY = 0;

        for(auto& piece: m_pieces){
            if(piece.first.x < minX){
                minX = piece.first.x;
            }
            if(piece.first.x > maxX){
                maxX = piece.first.x;
            }
            if(piece.first.y < minY){
                minY = piece.first.y;
            }
            if(piece.first.y > maxY){
                maxY = piece.first.y;
            }
        }

        for(int x = minX; x <= maxX; x++){
            for(int y = minY; y <= maxY; y++){
                auto it = m_pieces.find({x,y});
                if(it != m_pieces.end()){
                    m_pieces.insert({{x-1,y},it->second});
                    m_pieces.erase(it);
                }
            }
        }
    }

    if(m_circles.size() > 0){
        int minX = 2147483647;
        int maxX = 0;
        int minY = 2147483647;
        int maxY = 0;

        for(auto& circle: m_circles){
            if(circle.first.x < minX){
                minX = circle.first.x;
            }
            if(circle.first.x > maxX){
                maxX = circle.first.x;
            }
            if(circle.first.y < minY){
                minY = circle.first.y;
            }
            if(circle.first.y > maxY){
                maxY = circle.first.y;
            }
        }

        for(int x = minX; x <= maxX; x++){
            for(int y = minY; y <= maxY; y++){
                auto it = m_circles.find({x,y});
                if(it != m_circles.end()){
                    m_circles.insert({{x-1,y},it->second});
                    m_circles.erase(it);
                }
            }
        }
    }
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
