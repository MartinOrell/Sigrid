#include "Arrow.h"

using namespace sigrid;

Arrow::Arrow(const Coord& fromCoord, const Coord& toCoord, const int colorId, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const sf::Color& color)
: m_logicArrow(fromCoord, toCoord, colorId)
, m_graphicArrow(fromPosition, toPosition, color){}


Coord Arrow::fromCoord() const{
    return m_logicArrow.fromCoord();
}
Coord Arrow::toCoord() const{
    return m_logicArrow.toCoord();
}

void Arrow::set(const Coord& fromCoord, const Coord& toCoord, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition){
    m_logicArrow.set(fromCoord, toCoord);
    m_graphicArrow.set(fromPosition, toPosition);
}

void Arrow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_graphicArrow);
}