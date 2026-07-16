#include "Entity/Shape/Arrow/GraphicArrows.h"

#include "Entity/Shape/Arrow/LogicArrow.h"
#include "Color/ColorManager.h"
#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

using namespace sigrid;

void GraphicArrows::setThickness(const float& thickness){
    m_arrowThickness = thickness;
}

void GraphicArrows::setHeadSize(const float& headSize){
    m_arrowHeadSize = headSize;
}

void GraphicArrows::setColorManagerPtr(ColorManager* const managerPtr){
    m_colorManagerPtr = managerPtr;
}

void GraphicArrows::addArrow(const sigrid_coord::CoordPair& coordPair, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const LogicArrow& logicArrow){

    if(m_arrowThickness == 0.f){
        std::cerr << "GraphicArrows: Failed to add arrow, arrow thickness is 0" << std::endl;
        return;
    }
    if(m_arrowHeadSize == 0.f){
        std::cerr << "GraphicArrows: Failed to add arrow, arrow head size is 0" << std::endl;
        return;
    }

    sf::Color color;
    if(m_colorManagerPtr){
        auto color_o = m_colorManagerPtr->getSolidColor(logicArrow.getColorId());
        if(color_o != std::nullopt){
            color = color_o.value();
        }
        else{
            color = sf::Color::Black;
        }
    }
    else{
        color = sf::Color::Black;
    }

    GraphicArrow graphicArrow;
    graphicArrow.setFromPosition(fromPosition);
    graphicArrow.setToPosition(toPosition);
    graphicArrow.setColor(color);
    graphicArrow.setThickness(m_arrowThickness);
    graphicArrow.setHeadSize(m_arrowHeadSize);

    m_arrows.push_back(coordPair, graphicArrow);
}

void GraphicArrows::removeArrow(const sigrid_coord::CoordPair& coordPair){
    m_arrows.erase(coordPair);
}

float GraphicArrows::getThickness() const{
    return m_arrowThickness;
}

float GraphicArrows::getHeadSize() const{
    return m_arrowHeadSize;
}

std::optional<GraphicArrow> GraphicArrows::getArrow(const sigrid_coord::CoordPair& coordPair) const{
    return m_arrows.atKey(coordPair);
}

const sigrid_list::OrderedMap<sigrid_coord::CoordPair, GraphicArrow>& GraphicArrows::getArrows() const{
    return m_arrows;
}

sigrid_list::OrderedMap<sigrid_coord::CoordPair, GraphicArrow>& GraphicArrows::getArrows(){
    return m_arrows;
}

void GraphicArrows::clear(){
    m_arrows.clear();
}

void GraphicArrows::removeColumn(const int& columnId){

    for(int i = 0; i < m_arrows.size();){
        auto& coordPair_o = m_arrows.keyAt(i);
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

void GraphicArrows::removeRow(const int& rowId){

    for(int i = 0; i < m_arrows.size();){
        auto& coordPair_o = m_arrows.keyAt(i);
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

void GraphicArrows::moveArrowsRight(const float& tileWidth, const bool& isLeftToRight){
    
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
                    std::cout << "coordPair not found" << std::endl;
                    continue;
                }
                auto& coordPair = coordPair_o.value().get();

                if(coordPair.from != sigrid_coord::Coord{x,y}){
                    continue;
                }

                auto arrow_o = m_arrows.atKey(coordPair);
                if(arrow_o == std::nullopt){
                    std::cout << "arrow not found" << std::endl;
                    continue;
                }
                auto arrow = arrow_o.value().get();
                if(isLeftToRight){
                    arrow.move({tileWidth, 0.f});
                }

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.x++;
                newCoordPair.to.x++;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void GraphicArrows::moveArrowsLeft(const float& tileWidth, const bool& isLeftToRight){

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
                if(isLeftToRight){
                    arrow.move({-tileWidth, 0.f});
                }

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.x--;
                newCoordPair.to.x--;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void GraphicArrows::moveArrowsUp(const float& tileHeight, const bool& isTopToBottom){

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
                if(isTopToBottom){
                    arrow.move({0.f, -tileHeight});
                }

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.y--;
                newCoordPair.to.y--;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void GraphicArrows::moveArrowsDown(const float& tileHeight, const bool& isTopToBottom){

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
                if(isTopToBottom){
                    arrow.move({0.f, tileHeight});
                }

                sigrid_coord::CoordPair newCoordPair = coordPair;
                newCoordPair.from.y++;
                newCoordPair.to.y++;
                
                m_arrows.insert(i, newCoordPair, arrow);
                m_arrows.erase(i+1);
            }
        }
    }
}

void GraphicArrows::move(const sf::Vector2f& offset){

    for(int i = 0; i < m_arrows.size(); i++){
        auto arrow_o = m_arrows.atPosition(i);
        if(arrow_o == std::nullopt){
            continue;
        }
        auto& arrow = arrow_o.value().get();
        arrow.move(offset);
    }
}

void GraphicArrows::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    for(int i = 0; i < m_arrows.size(); i++){
        auto arrow_o = m_arrows.atPosition(i);
        if(arrow_o == std::nullopt){
            continue;
        }
        auto& arrow = arrow_o.value().get();
        target.draw(arrow);
    }
}