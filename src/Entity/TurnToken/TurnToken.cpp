#include "TurnToken.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sigrid;

TurnToken::TurnToken(){}

void TurnToken::setRadius(const float& radius){

    m_shape.setRadius(radius);
    m_shape.setOrigin({radius, radius});
}

void TurnToken::setCenterPosition(const sf::Vector2f& centerPosition){

    m_shape.setPosition(centerPosition);
}

void TurnToken::setTurnToMove(const int& turnToMove){

    m_shape.setFillColor(getColor(turnToMove));
}

TurnToken& TurnToken::operator =(const TurnToken& rhs){

    m_isInitialized = rhs.m_isInitialized;
    m_isVisible = rhs.m_isVisible;

    m_shape.setRadius(rhs.m_shape.getRadius());
    m_shape.setOrigin({rhs.m_shape.getRadius(),rhs.m_shape.getRadius()});
    m_shape.setPointCount(rhs.m_shape.getPointCount());
    m_shape.setPosition(rhs.m_shape.getPosition());
    m_shape.setFillColor(rhs.m_shape.getFillColor());
    m_shape.setOutlineColor(rhs.m_shape.getOutlineColor());
    m_shape.setOutlineThickness(rhs.m_shape.getOutlineThickness());

    return *this;
}

bool TurnToken::isVisible() const{
    return m_isVisible;
}

bool TurnToken::isHidden() const{
    return !m_isVisible;
}

bool TurnToken::isWithin(const sf::Vector2f& point) const{

    if(!m_isVisible){
        return false;
    }

    if(!m_isInitialized){
        return false;
    }

    float x = point.x;
    float y = point.y;

    float radius = m_shape.getRadius();
    sf::Vector2f center = getCenterPosition();

    return (x-center.x)*(x-center.x)+(y-center.y)*(y-center.y) < radius*radius;
}

float TurnToken::getRadius() const{
    return m_shape.getRadius();
}

sf::Vector2f TurnToken::getCenterPosition() const{
    return m_shape.getPosition();
}

void TurnToken::show(){

    m_isVisible = true;

    if(!m_isInitialized){
        init();
    }
}

void TurnToken::hide(){
    m_isVisible = false;
}

void TurnToken::move(const sf::Vector2f& offset){
    m_shape.move(offset);
}

void TurnToken::init(){

    m_shape.setPointCount(30);
    m_shape.setOutlineColor(sf::Color{0,0,0,255});
    m_shape.setOutlineThickness(-6.f);
    m_isInitialized = true;
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

    if(!m_isInitialized){
        return;
    }
    if(!m_isVisible){
        return;
    }
    target.draw(m_shape);
}
