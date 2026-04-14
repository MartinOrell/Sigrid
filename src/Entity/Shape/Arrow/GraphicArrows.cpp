#include "GraphicArrows.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>

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

void GraphicArrows::removeColumn(const int& columnId){

    for(auto arrowIt = m_arrows.begin(); arrowIt != m_arrows.end();){
        if(arrowIt->first.from.x == columnId || arrowIt->first.to.x == columnId){
            for(auto orderIt = m_drawOrder.begin(); orderIt != m_drawOrder.end(); orderIt++){
                if(*orderIt == arrowIt->first){
                    m_drawOrder.erase(orderIt);
                    break;
                }
            }
            arrowIt = m_arrows.erase(arrowIt);
        }
        else{
            arrowIt++;
        }
    }
}

void GraphicArrows::removeRow(const int& rowId){

    for(auto arrowIt = m_arrows.begin(); arrowIt != m_arrows.end();){
        if(arrowIt->first.from.y == rowId || arrowIt->first.to.y == rowId){
            for(auto orderIt = m_drawOrder.begin(); orderIt != m_drawOrder.end(); orderIt++){
                if(*orderIt == arrowIt->first){
                    m_drawOrder.erase(orderIt);
                    break;
                }
            }
            arrowIt = m_arrows.erase(arrowIt);
        }
        else{
            arrowIt++;
        }
    }
}

void GraphicArrows::moveArrowsRight(const float& tileWidth, const bool& isLeftToRight){
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

            auto isFrom = [&x, &y](std::pair<CoordPair,GraphicArrow> arrow) {
                return arrow.first.from == Coord{x,y};
            };

            for(auto arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom);arrowIt != m_arrows.end();arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom)){
                Coord from{x+1,y};
                Coord to{arrowIt->first.to.x+1,arrowIt->first.to.y};
                for(auto orderIt = m_drawOrder.begin(); orderIt != m_drawOrder.end(); orderIt++){
                    if(*orderIt == arrowIt->first){
                        m_drawOrder.erase(orderIt);
                        break;
                    }
                }
                m_drawOrder.push_back({from, to});
                m_arrows.insert({{from,to},arrowIt->second});
                if(isLeftToRight){
                    m_arrows.at({from,to}).move({tileWidth, 0.f});
                }
                m_arrows.erase(arrowIt);
            }
        }
    }
}

void GraphicArrows::moveArrowsLeft(const float& tileWidth, const bool& isLeftToRight){

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

            auto isFrom = [&x, &y](std::pair<CoordPair,GraphicArrow> arrow) {
                return arrow.first.from == Coord{x,y};
            };

            for(auto arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom);arrowIt != m_arrows.end();arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom)){
                Coord from{x-1,y};
                Coord to{arrowIt->first.to.x-1,arrowIt->first.to.y};
                for(auto orderIt = m_drawOrder.begin(); orderIt != m_drawOrder.end(); orderIt++){
                    if(*orderIt == arrowIt->first){
                        m_drawOrder.erase(orderIt);
                        break;
                    }
                }
                m_drawOrder.push_back({from, to});
                m_arrows.insert({{from,to},arrowIt->second});
                if(isLeftToRight){
                    m_arrows.at({from,to}).move({-tileWidth, 0.f});
                }
                m_arrows.erase(arrowIt);
            }
        }
    }
}

void GraphicArrows::moveArrowsUp(const float& tileHeight, const bool& isTopToBottom){

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

    for(int y = minY; y <= maxY; y++){
        for(int x = minX; x <= maxX; x++){

            auto isFrom = [&x, &y](std::pair<CoordPair,GraphicArrow> arrow) {
                return arrow.first.from == Coord{x,y};
            };

            for(auto arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom);arrowIt != m_arrows.end();arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom)){
                Coord from{x,y-1};
                Coord to{arrowIt->first.to.x,arrowIt->first.to.y-1};
                for(auto orderIt = m_drawOrder.begin(); orderIt != m_drawOrder.end(); orderIt++){
                    if(*orderIt == arrowIt->first){
                        m_drawOrder.erase(orderIt);
                        break;
                    }
                }
                m_drawOrder.push_back({from, to});
                m_arrows.insert({{from,to},arrowIt->second});
                if(isTopToBottom){
                    m_arrows.at({from,to}).move({0.f, -tileHeight});
                }
                m_arrows.erase(arrowIt);
            }
        }
    }
}

void GraphicArrows::moveArrowsDown(const float& tileHeight, const bool& isTopToBottom){

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

    for(int y = maxY; y >= minY; y--){
        for(int x = minX; x <= maxX; x++){

            auto isFrom = [&x, &y](std::pair<CoordPair,GraphicArrow> arrow) {
                return arrow.first.from == Coord{x,y};
            };

            for(auto arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom);arrowIt != m_arrows.end();arrowIt = std::find_if(m_arrows.begin(),m_arrows.end(),isFrom)){
                Coord from{x,y+1};
                Coord to{arrowIt->first.to.x,arrowIt->first.to.y+1};
                for(auto orderIt = m_drawOrder.begin(); orderIt != m_drawOrder.end(); orderIt++){
                    if(*orderIt == arrowIt->first){
                        m_drawOrder.erase(orderIt);
                        break;
                    }
                }
                m_drawOrder.push_back({from, to});
                m_arrows.insert({{from,to},arrowIt->second});
                if(isTopToBottom){
                    m_arrows.at({from,to}).move({0.f, tileHeight});
                }
                m_arrows.erase(arrowIt);
            }
        }
    }
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