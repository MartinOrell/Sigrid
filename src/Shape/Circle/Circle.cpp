#include "Circle.h"

using namespace sigrid;

Circle::Circle(const Coord& coord, const int colorId, const sf::Vector2f& position, const sf::Color& color, const float& diameter)
: m_logic(coord, colorId)
, m_graphic(position, color, diameter){}


Coord Circle::getCoord() const{
    return m_logic.getPosition();
}

void Circle::setPosition(const Coord& coord, const sf::Vector2f& position){
    m_logic.setPosition(coord);
    m_graphic.setPosition(position);
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_graphic);
}