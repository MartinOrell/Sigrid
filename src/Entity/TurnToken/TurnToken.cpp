#include "TurnToken.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

using namespace sigrid;

TurnToken::TurnToken()
: m_isVisible(true){}

void TurnToken::init(const float& radius, const sf::Vector2f& centerPosition, const int& turnToMove){

    std::size_t pointCount = 30;
    m_shapePtr = std::make_unique<sf::CircleShape>(radius, pointCount);
    m_shapePtr->setPosition(centerPosition - sf::Vector2f{radius, radius});

    m_shapePtr->setFillColor(getColor(turnToMove));
    m_shapePtr->setOutlineColor(sf::Color{0,0,0,255});
    m_shapePtr->setOutlineThickness(-6.f);
}

TurnToken& TurnToken::operator =(const TurnToken& rhs){
    m_isVisible = rhs.m_isVisible;

    if(rhs.m_shapePtr){
        if(!m_shapePtr){
            m_shapePtr = std::make_unique<sf::CircleShape>();
        }
        m_shapePtr->setRadius(rhs.m_shapePtr->getRadius());
        m_shapePtr->setPointCount(rhs.m_shapePtr->getPointCount());
        m_shapePtr->setPosition(rhs.m_shapePtr->getPosition());
        m_shapePtr->setFillColor(rhs.m_shapePtr->getFillColor());
        m_shapePtr->setOutlineColor(rhs.m_shapePtr->getOutlineColor());
        m_shapePtr->setOutlineThickness(rhs.m_shapePtr->getOutlineThickness());
    }
    return *this;
}

bool TurnToken::isVisible() const{
    return m_isVisible;
}

bool TurnToken::isWithin(const sf::Vector2f& point){

    if(!m_isVisible){
        return false;
    }

    if(!m_shapePtr){
        return false;
    }

    float x = point.x;
    float y = point.y;

    float radius = m_shapePtr->getRadius();
    sf::Vector2f center = getCenterPosition();

    return (x-center.x)*(x-center.x)+(y-center.y)*(y-center.y) < radius*radius;
}

float TurnToken::getRadius() const{
    if(!m_shapePtr){
        return 0.f;
    }
    return m_shapePtr->getRadius();
}

sf::Vector2f TurnToken::getCenterPosition() const{
    if(!m_shapePtr){
        return {0.f,0.f};
    }
    float radius = m_shapePtr->getRadius();
    return m_shapePtr->getPosition()+sf::Vector2f{radius,radius};
}

void TurnToken::show(){
    m_isVisible = true;
}

void TurnToken::hide(){
    m_isVisible = false;
}

void TurnToken::setTurnToMove(const int& turnToMove){
    if(!m_shapePtr){
        return;
    }

    m_shapePtr->setFillColor(getColor(turnToMove));
}

void TurnToken::move(const sf::Vector2f& offset){
    if(!m_shapePtr){
        return;
    }
    m_shapePtr->move(offset);
}

sf::Color TurnToken::getColor(const int& turnToMove) const{
    if(turnToMove == 1){
        return sf::Color{0,0,0,255};
    }
    else{
        return sf::Color{255,255,255,255};
    }
}

void TurnToken::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(!m_shapePtr){
        return;
    }
    if(!m_isVisible){
        return;
    }
    target.draw(*m_shapePtr);
}
