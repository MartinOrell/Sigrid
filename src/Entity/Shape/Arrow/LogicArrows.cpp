#include "Entity/Shape/Arrow/LogicArrows.h"

using namespace sigrid;

LogicArrows::LogicArrows(){}

void LogicArrows::addArrow(const CoordPair& coordPair, const LogicArrow& arrow){
    m_arrows.push_back(coordPair, arrow);
}
            
void LogicArrows::removeArrow(const CoordPair& coordPair){
    m_arrows.erase(coordPair);
}
            
std::optional<LogicArrow> LogicArrows::getArrow(const CoordPair& coordPair) const{

    auto arrow_o = m_arrows.at(coordPair);

    if(arrow_o == std::nullopt){
        return std::nullopt;
    }
    return arrow_o.value().get();
}

void LogicArrows::removeColumn(const int& columnId){

    for(unsigned int i = 0; i < m_arrows.size();){
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

    for(unsigned int i = 0; i < m_arrows.size();){
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

    for(unsigned int i = 0; i < m_arrows.size(); i++){
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

            for(unsigned int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.at(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                CoordPair newCoordPair = coordPair;
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

    for(unsigned int i = 0; i < m_arrows.size(); i++){
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


            for(unsigned int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.at(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                CoordPair newCoordPair = coordPair;
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

    for(unsigned int i = 0; i < m_arrows.size(); i++){
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

            for(unsigned int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.at(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                CoordPair newCoordPair = coordPair;
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

    for(unsigned int i = 0; i < m_arrows.size(); i++){
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

            for(unsigned int i = 0; i < m_arrows.size(); i++){
                auto coordPair_o = m_arrows.keyAt(i);
                if(coordPair_o == std::nullopt){
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.at(coordPair);
                if(arrow_o == std::nullopt){
                    continue;
                }
                auto arrow = arrow_o.value().get();

                CoordPair newCoordPair = coordPair;
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