#include "GraphicArrows.h"

using namespace sigrid;

GraphicArrows::GraphicArrows(){}

void GraphicArrows::init(const float& arrowThickness, const float& arrowHeadSize){

    m_arrowThickness = arrowThickness;
    m_arrowHeadSize = arrowHeadSize;
}

std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator GraphicArrows::begin(){

    return m_arrows.begin();
}

std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator GraphicArrows::end(){
    
    return m_arrows.end();
}

void GraphicArrows::addArrow(const CoordPair& coordPair, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const sf::Color& color){
    
    GraphicArrow graphicArrow;
    graphicArrow.init(fromPosition, toPosition, color, m_arrowThickness, m_arrowHeadSize);

    m_arrows.insert({coordPair, graphicArrow});
}

void GraphicArrows::removeArrow(const CoordPair& coordPair){

    m_arrows.erase(coordPair);
}

float GraphicArrows::getThickness() const{

    return m_arrowThickness;
}

float GraphicArrows::getHeadSize() const{

    return m_arrowHeadSize;
}

std::optional<GraphicArrow> GraphicArrows::getArrow(const CoordPair& coordPair) const{

    auto it = m_arrows.find(coordPair);

    if(it == m_arrows.end()){
        return std::nullopt;
    }

    return it->second;
}

void GraphicArrows::move(const sf::Vector2f& offset){

    for(auto& arrow: m_arrows){
        arrow.second.move(offset);
    }
}

void GraphicArrows::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(auto& arrow : m_arrows){
        target.draw(arrow.second);
    }
}