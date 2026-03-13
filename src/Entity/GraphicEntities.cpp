#include "GraphicEntities.h"

#include <iostream>

using namespace sigrid;

GraphicEntities::GraphicEntities(){}

void GraphicEntities::addPiece(const Coord& coord, const GraphicPiece& piece){
    m_pieces.insert({coord, piece});
}

void GraphicEntities::addCircle(const Coord& coord, const GraphicCircle& circle){
    m_circles.insert({coord, circle});
}

void GraphicEntities::removeEntity(const Coord& coord){
    m_pieces.erase(coord);
    m_circles.erase(coord);
}

void GraphicEntities::clear(){
    m_pieces.clear();
    m_circles.clear();
}

std::optional<GraphicPiece> GraphicEntities::getPieceAt(const Coord& coord) const{
    auto it = m_pieces.find(coord);
    if(it != m_pieces.end()){
        return it->second;
    }
    return std::nullopt;
}

std::optional<GraphicCircle> GraphicEntities::getCircleAt(const Coord& coord) const{
    auto it = m_circles.find(coord);
    if(it != m_circles.end()){
        return it->second;
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