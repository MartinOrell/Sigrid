#include "GraphicArrows.h"

#include <iostream>

using namespace sigrid;

GraphicArrows::GraphicArrows(){}

void GraphicArrows::init(const float& arrowThickness, const float& arrowHeadSize, ColorManager* const colorManagerPtr){

    m_colorManagerPtr = colorManagerPtr;
    m_arrowThickness = arrowThickness;
    m_arrowHeadSize = arrowHeadSize;
}

std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator GraphicArrows::begin(){

    return m_arrows.begin();
}

std::map<sigrid::CoordPair, sigrid::GraphicArrow>::iterator GraphicArrows::end(){
    
    return m_arrows.end();
}

void GraphicArrows::addArrow(const CoordPair& coordPair, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const LogicArrow& logicArrow){

    auto color_o = m_colorManagerPtr->getSolidColor(logicArrow.getColorId());

    sf::Color color;
    if(color_o != std::nullopt){
        color = color_o.value();
    }

    GraphicArrow graphicArrow;
    graphicArrow.init(fromPosition, toPosition, color, m_arrowThickness, m_arrowHeadSize);

    m_arrows.insert({coordPair, graphicArrow});
    m_drawOrder.push_back(coordPair);
}

void GraphicArrows::removeArrow(const CoordPair& coordPair){

    m_arrows.erase(coordPair);

    for(auto it = m_drawOrder.begin(); it != m_drawOrder.end(); it++){
        if(*it == coordPair){
            m_drawOrder.erase(it);
            break;
        }
    }
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

void GraphicArrows::clear(){
    m_arrows.clear();
    m_drawOrder.clear();
}

void GraphicArrows::move(const sf::Vector2f& offset){

    for(auto& arrow: m_arrows){
        arrow.second.move(offset);
    }
}

void GraphicArrows::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(auto& coordPair: m_drawOrder){
        auto it = m_arrows.find(coordPair);
        if(it == m_arrows.end()){
            std::cout << "Failed to draw arrow at " << coordPair.getNotation() << std::endl;
            continue;
        }
        target.draw(it->second);
    }
}