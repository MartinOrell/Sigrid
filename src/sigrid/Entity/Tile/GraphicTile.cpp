#include "sigrid/Entity/Tile/GraphicTile.h"

#include <SFML/Graphics/RenderTarget.hpp>

void sigrid::GraphicTile::setSize(const sigrid::Size_f& size){

    m_shape.setSize(size.getSfPosition());
    if(m_isHighlightVisible){
        m_highlight.setSize(size.getSfPosition());
    }
}

void sigrid::GraphicTile::setPosition(const sigrid::Position_f& topLeftPosition){

    m_shape.setPosition(topLeftPosition.getSfPosition());
    if(m_isHighlightVisible){
        m_highlight.setPosition(topLeftPosition.getSfPosition());
    }
}

void sigrid::GraphicTile::setTileColor(const sigrid::Color& color){
    m_shape.setFillColor(color.getSfColor());
}

void sigrid::GraphicTile::setHighlightColor(const sigrid::Color& color){

    if(!m_isHighlightVisible){
        m_isHighlightVisible = true;
        m_highlight.setSize(m_shape.getSize());
        m_highlight.setPosition(m_shape.getPosition());
    }

    m_highlight.setFillColor(color.getSfColor());
}

void sigrid::GraphicTile::removeHighlight(){
    m_isHighlightVisible = false;
}

sigrid::Size_f sigrid::GraphicTile::getSize() const{

    sigrid::Size_f size;
    size.set(m_shape.getSize());
    return size;
}

sigrid::Position_f sigrid::GraphicTile::getTopLeftPosition() const{
    
    sigrid::Position_f position;
    position.set(m_shape.getPosition());
    return position;
}

sigrid::Position_f sigrid::GraphicTile::getCentrePosition() const{
    return getTopLeftPosition() + getSize()/2.f;
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