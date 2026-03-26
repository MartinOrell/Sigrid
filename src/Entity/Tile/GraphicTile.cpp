#include "GraphicTile.h"

#include <iostream>

using namespace sigrid;

GraphicTile::GraphicTile(){}

void GraphicTile::init(const sf::Vector2f& size, const sf::Color& color){
    m_shape.setSize(size);
    m_shape.setFillColor(color);
}

void GraphicTile::setPosition(const sf::Vector2f& topLeftPosition){
    m_shape.setPosition(topLeftPosition);
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

GraphicTile& GraphicTile::operator =(const GraphicTile& rhs){
    m_shape = rhs.m_shape;
    return *this;
}

void GraphicTile::move(const sf::Vector2f& offset){
    m_shape.move(offset);
}

void GraphicTile::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}