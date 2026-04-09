#include "LogicArrows.h"

using namespace sigrid;

LogicArrows::LogicArrows(){}

void LogicArrows::addArrow(const CoordPair& coordPair, const LogicArrow& arrow){
    m_arrows.insert({coordPair, arrow});
}
            
void LogicArrows::removeArrow(const CoordPair& coordPair){
    m_arrows.erase(coordPair);
}
            
std::optional<LogicArrow> LogicArrows::getArrow(const CoordPair& coordPair) const{
    auto it = m_arrows.find(coordPair);

    if(it == m_arrows.end()){
        return std::nullopt;
    }

    return it->second;
}

void LogicArrows::removeColumn(const int& columnId){
    for(auto it = m_arrows.begin(); it != m_arrows.end();){
        if(it->first.from.x == columnId || it->first.to.x == columnId){
            it = m_arrows.erase(it);
        }
        else{
            it++;
        }
    }
}

void LogicArrows::moveArrowsRight(){

    if(m_arrows.size() > 0){
        int minX = 2147483647;
        int maxX = 0;
        int minY = 2147483647;
        int maxY = 0;

        for(auto& arrow: m_arrows){
            if(arrow.first.from.x < minX){
                minX = arrow.first.from.x;
            }
            if(arrow.first.from.x > maxX){
                maxX = arrow.first.from.x;
            }
            if(arrow.first.from.y < minY){
                minY = arrow.first.from.y;
            }
            if(arrow.first.from.y > maxY){
                maxY = arrow.first.from.y;
            }
        }

        for(int x = maxX; x >= minX; x--){
            for(int y = minY; y <= maxY; y++){

                auto isFrom = [&x, &y](std::pair<CoordPair,LogicArrow> arrow) {
                    return arrow.first.from == Coord{x,y};
                };

                ;
                for(auto it = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom);it != m_arrows.end();it = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom)){
                    Coord from{x+1,y};
                    Coord to{it->first.to.x+1,it->first.to.y};
                    m_arrows.insert({{from,to},it->second});
                    m_arrows.erase(it);
                }
            }
        }
    }
}

void LogicArrows::moveArrowsLeft(){

    if(m_arrows.size() > 0){
        int minX = 2147483647;
        int maxX = 0;
        int minY = 2147483647;
        int maxY = 0;

        for(auto& arrow: m_arrows){
            if(arrow.first.from.x < minX){
                minX = arrow.first.from.x;
            }
            if(arrow.first.from.x > maxX){
                maxX = arrow.first.from.x;
            }
            if(arrow.first.from.y < minY){
                minY = arrow.first.from.y;
            }
            if(arrow.first.from.y > maxY){
                maxY = arrow.first.from.y;
            }
        }

        for(int x = minX; x <= maxX; x++){
            for(int y = minY; y <= maxY; y++){

                auto isFrom = [&x, &y](std::pair<CoordPair,LogicArrow> arrow) {
                    return arrow.first.from == Coord{x,y};
                };

                ;
                for(auto it = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom);it != m_arrows.end();it = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom)){
                    Coord from{x-1,y};
                    Coord to{it->first.to.x-1,it->first.to.y};
                    m_arrows.insert({{from,to},it->second});
                    m_arrows.erase(it);
                }
            }
        }
    }
}

void LogicArrows::clear(){
    m_arrows.clear();
}