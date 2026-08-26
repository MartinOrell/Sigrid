#include "sigrid/Entity/Tile/GraphicTile.h"

#include <SFML/Graphics/RenderTarget.hpp>

void sigrid::GraphicTile::setSize(const sf::Vector2f& size){

    m_shape.setSize(size);
    if(m_isHighlightVisible){
        m_highlight.setSize(size);
    }
}

void sigrid::GraphicTile::setPosition(const sf::Vector2f& topLeftPosition){

    m_shape.setPosition(topLeftPosition);
    if(m_isHighlightVisible){
        m_highlight.setPosition(topLeftPosition);
    }
}

void sigrid::GraphicTile::setTileColor(const sf::Color& color){
    m_shape.setFillColor(color);
}

void sigrid::GraphicTile::setHighlightColor(const sf::Color& color){

    if(!m_isHighlightVisible){
        m_isHighlightVisible = true;
        m_highlight.setSize(m_shape.getSize());
        m_highlight.setPosition(m_shape.getPosition());
    }

    m_highlight.setFillColor(color);
}

void sigrid::GraphicTile::removeHighlight(){
    m_isHighlightVisible = false;
}

sf::Vector2f sigrid::GraphicTile::getSize() const{
    return m_shape.getSize();
}

sf::Vector2f sigrid::GraphicTile::getTopLeftPosition() const{
    return m_shape.getPosition();
}

sf::Vector2f sigrid::GraphicTile::getCentrePosition() const{
    return m_shape.getPosition() + m_shape.getSize()/2.f;
}

float sigrid::GraphicTile::getRightPosition() const{
    return m_shape.getPosition().x + m_shape.getSize().x;
}

float sigrid::GraphicTile::getTopPosition() const{
    return m_shape.getPosition().y;
}

sigrid::Color sigrid::GraphicTile::getColor() const{

    sigrid::Color color;
    color.setRGBA(m_shape.getFillColor().toInteger());
    return color;
}

void sigrid::GraphicTile::move(const sf::Vector2f& offset){

    m_shape.move(offset);
    if(m_isHighlightVisible){
        m_highlight.move(offset);
    }
}

void sigrid::GraphicTile::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(m_shape);
    if(m_isHighlightVisible){
        target.draw(m_highlight);
    }
}