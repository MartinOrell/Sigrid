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