#include "Entity/Tile/GraphicTile.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sigrid;

GraphicTile::GraphicTile(){}

void GraphicTile::setSize(const sf::Vector2f& size){

    m_shape.setSize(size);
    if(m_isHighlightVisible){
        m_highlight.setSize(size);
    }
}

void GraphicTile::setPosition(const sf::Vector2f& topLeftPosition){

    m_shape.setPosition(topLeftPosition);
    if(m_isHighlightVisible){
        m_highlight.setPosition(topLeftPosition);
    }
}

void GraphicTile::setTileColor(const sf::Color& color){
    m_shape.setFillColor(color);
}

void GraphicTile::setHighlightColor(const sf::Color& color){

    if(!m_isHighlightVisible){
        m_isHighlightVisible = true;
        m_highlight.setSize(m_shape.getSize());
        m_highlight.setPosition(m_shape.getPosition());
    }

    m_highlight.setFillColor(color);
}

void GraphicTile::removeHighlight(){
    m_isHighlightVisible = false;
}

sf::Vector2f GraphicTile::getSize() const{
    return m_shape.getSize();
}

sf::Vector2f GraphicTile::getTopLeftPosition() const{
    return m_shape.getPosition();
}

sf::Vector2f GraphicTile::getCentrePosition() const{
    return m_shape.getPosition() + m_shape.getSize()/2.f;
}

float GraphicTile::getRightPosition() const{
    return m_shape.getPosition().x + m_shape.getSize().x;
}

float GraphicTile::getTopPosition() const{
    return m_shape.getPosition().y;
}

sf::Color GraphicTile::getColor() const{
    return m_shape.getFillColor();
}

void GraphicTile::move(const sf::Vector2f& offset){

    m_shape.move(offset);
    if(m_isHighlightVisible){
        m_highlight.move(offset);
    }
}

void GraphicTile::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(m_shape);
    if(m_isHighlightVisible){
        target.draw(m_highlight);
    }
}