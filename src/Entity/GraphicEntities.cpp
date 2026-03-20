#include "GraphicEntities.h"

#include <iostream>

using namespace sigrid;

GraphicEntities::GraphicEntities(const sf::Vector2f& pieceSize, const float& circleDiameter, PieceManager* const pieceManagerPtr, ColorManager* const colorManagerPtr)
: m_pieceSize{pieceSize}
, m_circleDiameter{circleDiameter}
, m_pieceManagerPtr{pieceManagerPtr}
, m_colorManagerPtr{colorManagerPtr}{}

void GraphicEntities::addEntity(const Coord& coord, const sf::Vector2f position, const LogicEntity& entity){
    if(std::holds_alternative<LogicPiece>(entity)){
        if(m_pieceManagerPtr == nullptr){
            std::cout << "GraphicEntities: Failed to add piece" << std::endl;
            std::cout << "PieceManagerPtr is null" << std::endl;
            return;
        }

        auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(std::get<LogicPiece>(entity));

        if(graphicPiece_o == std::nullopt){
            std::cout << "GraphicEntities: Failed to add piece" << std::endl;
            std::cout << "Piece not found in pieceManager" << std::endl;
            return;
        }

        GraphicPiece newPiece{graphicPiece_o.value()};
        newPiece.resize(m_pieceSize);
        newPiece.setPosition(position);
        m_pieces.insert({coord, newPiece});
    }
    else if(std::holds_alternative<LogicCircle>(entity)){
        if(m_colorManagerPtr == nullptr){
            std::cout << "GraphicEntities: Unable to add circle at " << coord.getNotation() << std::endl;
            std::cout << "ColorManager does not exist to assign color" << std::endl;
            return;
        }

        int colorId = std::get<LogicCircle>(entity).getColorId();
        auto color_o = m_colorManagerPtr->getSolidColor(colorId);
        if(color_o == std::nullopt){
            std::cout << "GraphicEntities: Unable to add circle at " << coord.getNotation() << std::endl;
            std::cout << "Color of colorId " << colorId << " not found" << std::endl;
            return;
        }

        GraphicCircle newCircle(color_o.value(), m_circleDiameter);
        newCircle.setPosition(position);
        m_circles.insert({coord, newCircle});
    }
}

void GraphicEntities::removeEntity(const Coord& coord){
    m_pieces.erase(coord);
    m_circles.erase(coord);
}

void GraphicEntities::moveEntity(const Coord& fromCoord, const Coord& toCoord, const sf::Vector2f& newPosition){
    {
        auto it = m_pieces.find(fromCoord);
        if(it != m_pieces.end()){
            GraphicPiece piece{it->second};
            piece.setPosition(newPosition);
            m_pieces.insert({toCoord, piece});
            m_pieces.erase(fromCoord);
            return;
        }
    }
    {
        auto it = m_circles.find(fromCoord);
        if(it != m_circles.end()){
            GraphicCircle circle{it->second};
            circle.setPosition(newPosition);
            m_circles.insert({toCoord, circle});
            m_circles.erase(fromCoord);
            return;
        }
    }
}

void GraphicEntities::clear(){
    m_pieces.clear();
    m_circles.clear();
}

std::optional<GraphicEntity> GraphicEntities::getEntityAt(const Coord& coord) const{
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

void GraphicEntities::move(const sf::Vector2f& offset){
    for(auto& piece : m_pieces){
        piece.second.move(offset);
    }

    for(auto& circle : m_circles){
        circle.second.move(offset);
    }
}

void GraphicEntities::setEntityPosition(const Coord& coord, const sf::Vector2f& position){
    {
        auto it = m_pieces.find(coord);
        if(it != m_pieces.end()){
            it->second.setPosition(position);
            return;
        }
    }
    {
        auto it = m_circles.find(coord);
        if(it != m_circles.end()){
            it->second.setPosition(position);
            return;
        }
    }
}

void GraphicEntities::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(auto& piece : m_pieces){
        target.draw(piece.second);
    }

    for(auto& circle : m_circles){
        target.draw(circle.second);
    }
}