#include "sigrid/Entity/Shape/Arrow/LogicArrows.h"

#include <iostream>

#include "sigrid/Entity/Shape/Arrow/ArrowDataContainer.h"

using namespace sigrid;

void LogicArrows::addArrow(const sigrid_coord::CoordPair& coordPair, const LogicArrow& arrow){
    m_arrows.push_back(coordPair, arrow);
}
            
void LogicArrows::removeArrow(const sigrid_coord::CoordPair& coordPair){
    m_arrows.erase(coordPair);
}

int LogicArrows::size() const{
    return m_arrows.size();
}

std::optional<LogicArrow> LogicArrows::getArrowAtIndex(const int& index) const{

    auto arrow_o = m_arrows.atPosition(index);

    if(arrow_o == std::nullopt){
        return std::nullopt;
    }
    return arrow_o.value().get();
}

std::optional<sigrid_coord::CoordPair> LogicArrows::getArrowKeyAtIndex(const int& index) const{

    auto coordPair_o = m_arrows.keyAt(index);

    if(coordPair_o == std::nullopt){
        return std::nullopt;
    }
    return coordPair_o.value().get();
}
            
std::optional<LogicArrow> LogicArrows::getArrow(const sigrid_coord::CoordPair& coordPair) const{

    auto arrow_o = m_arrows.atKey(coordPair);

    if(arrow_o == std::nullopt){
        return std::nullopt;
    }
    return arrow_o.value().get();
}

void LogicArrows::removeColumn(const int& columnId){

    for(int i = 0; i < m_arrows.size();){
        auto coordPair_o = m_arrows.keyAt(i);
        if(coordPair_o == std::nullopt){
            i++;
            continue;
        }
        auto& coordPair = coordPair_o.value().get();

        if(coordPair.from.x == columnId){
            m_arrows.erase(i);
            continue;
        }

        if(coordPair.to.x == columnId){
            m_arrows.erase(i);
            continue;
        }

        i++;
    }
}

void LogicArrows::removeRow(const int& rowId){

    for(int i = 0; i < m_arrows.size();){
        auto coordPair_o = m_arrows.keyAt(i);
        if(coordPair_o == std::nullopt){
            i++;
            continue;
        }
        auto& coordPair = coordPair_o.value().get();

        if(coordPair.from.y == rowId){
            m_arrows.erase(i);
            continue;
        }

        if(coordPair.to.y == rowId){
            m_arrows.erase(i);
            continue;
        }

        i++;
    }
}

void LogicArrows::moveArrowsRight(){

    if(m_arrows.size() == 0){
        return;
    }

    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(int i = 0; i < m_arrows.size(); i++){
        auto coordPair_o = m_arrows.keyAt(i);
        if(coordPair_o == std::nullopt){
            continue;
        }
        auto& coordPair = coordPair_o.value().get();

        if(coordPair.from.x < minX){
            minX = coordPair.from.x;
        }
        if(coordPair.from.x > maxX){
            maxX = coordPair.from.x;
        }
        if(coordPair.from.y < minY){
            minY = coordPair.from.y;
        }
        if(coordPair.from.y > maxY){
            maxY = coordPair.from.y;
        }
    }

    for(int x = maxX; x >= minX; x--){
        for(int y = minY; y <= maxY; y++){

            for(int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != sigrid_coord::Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.atKey(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.x++;
                newCoordPair.to.x++;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void LogicArrows::moveArrowsLeft(){

    if(m_arrows.size() == 0){
        return;
    }

    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(int i = 0; i < m_arrows.size(); i++){
        auto coordPair_o = m_arrows.keyAt(i);
        if(coordPair_o == std::nullopt){
            continue;
        }
        auto& coordPair = coordPair_o.value().get();

        if(coordPair.from.x < minX){
            minX = coordPair.from.x;
        }
        if(coordPair.from.x > maxX){
            maxX = coordPair.from.x;
        }
        if(coordPair.from.y < minY){
            minY = coordPair.from.y;
        }
        if(coordPair.from.y > maxY){
            maxY = coordPair.from.y;
        }
    }

    for(int x = minX; x <= maxX; x++){
        for(int y = minY; y <= maxY; y++){


            for(int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != sigrid_coord::Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.atKey(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.x--;
                newCoordPair.to.x--;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void LogicArrows::moveArrowsUp(){

    if(m_arrows.size() == 0){
        return;
    }

    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(int i = 0; i < m_arrows.size(); i++){
        auto coordPair_o = m_arrows.keyAt(i);
        if(coordPair_o == std::nullopt){
            continue;
        }
        auto& coordPair = coordPair_o.value().get();

        if(coordPair.from.x < minX){
            minX = coordPair.from.x;
        }
        if(coordPair.from.x > maxX){
            maxX = coordPair.from.x;
        }
        if(coordPair.from.y < minY){
            minY = coordPair.from.y;
        }
        if(coordPair.from.y > maxY){
            maxY = coordPair.from.y;
        }
    }

    for(int y = minY; y <= maxY; y++){
        for(int x = minX; x <= maxX; x++){

            for(int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != sigrid_coord::Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.atKey(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.y--;
                newCoordPair.to.y--;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void LogicArrows::moveArrowsDown(){

    if(m_arrows.size() == 0){
        return;
    }

    int minX = 2147483647;
    int maxX = 0;
    int minY = 2147483647;
    int maxY = 0;

    for(int i = 0; i < m_arrows.size(); i++){
        auto coordPair_o = m_arrows.keyAt(i);
        if(coordPair_o == std::nullopt){
            continue;
        }
        auto& coordPair = coordPair_o.value().get();

        if(coordPair.from.x < minX){
            minX = coordPair.from.x;
        }
        if(coordPair.from.x > maxX){
            maxX = coordPair.from.x;
        }
        if(coordPair.from.y < minY){
            minY = coordPair.from.y;
        }
        if(coordPair.from.y > maxY){
            maxY = coordPair.from.y;
        }
    }

    for(int y = maxY; y >= minY; y--){
        for(int x = minX; x <= maxX; x++){

            for(int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != sigrid_coord::Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.atKey(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.y++;
                newCoordPair.to.y++;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void LogicArrows::clear(){
    m_arrows.clear();
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicArrows &arrows)
{

    for(int i = 0; i < arrows.m_arrows.size(); i++){
        
        const auto& arrow_o = arrows.m_arrows.atPosition(i);
        if(arrow_o == std::nullopt){
            std::cerr << "LogicArrows: failed getting arrow at index " << i << "."
                << " Writing with operator << failed" << std::endl;
            return out;
        }
        const LogicArrow& arrow = arrow_o.value();

        const auto coordPair_o = arrows.m_arrows.keyAt(i);
        if(coordPair_o == std::nullopt){
            std::cerr << "LogicArrows: failed getting coordPair for arrow at index " << i << "."
                << " Writing with operator << failed" << std::endl;
            return out;
        }
        const sigrid_coord::CoordPair& coordPair = coordPair_o.value();

        ArrowDataContainer arrowData = arrow.getContainer();
        arrowData.position = coordPair.getNotation();

        out << "\n" << arrowData;
    }

    return out;
}