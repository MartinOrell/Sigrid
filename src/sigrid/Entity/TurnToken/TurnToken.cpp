#include "sigrid/Entity/TurnToken/TurnToken.h"

#include <SFML/Graphics/RenderTarget.hpp>

sigrid::TurnTokenContainer sigrid::TurnToken::getContainer() const{

    TurnTokenContainer container;
    container.isVisible = this->m_isVisible;

    return container;
}

void sigrid::TurnToken::setRadius(const float& radius){

    m_shape.setRadius(radius);
    m_shape.setOrigin({radius, radius});
}

void sigrid::TurnToken::setCenterPosition(const sf::Vector2f& centerPosition){

    m_shape.setPosition(centerPosition);
}

void sigrid::TurnToken::setTurnToMove(const int& turnToMove){

    m_shape.setFillColor(getColor(turnToMove).getSfColor());
}

bool sigrid::TurnToken::isVisible() const{
    return m_isVisible;
}

bool sigrid::TurnToken::isHidden() const{
    return !m_isVisible;
}

bool sigrid::TurnToken::isWithin(const sigrid::Position_f& point) const{

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

float sigrid::TurnToken::getRadius() const{
    return m_shape.getRadius();
}

sf::Vector2f sigrid::TurnToken::getCenterPosition() const{
    return m_shape.getPosition();
}

void sigrid::TurnToken::show(){

    m_isVisible = true;

    if(!m_isInitialized){
        init();
    }
}

void sigrid::TurnToken::hide(){
    m_isVisible = false;
}

void sigrid::TurnToken::move(const sf::Vector2f& offset){
    m_shape.move(offset);
}

void sigrid::TurnToken::init(){

    m_shape.setPointCount(30);
    m_shape.setOutlineColor(sf::Color{0,0,0,255});
    m_shape.setOutlineThickness(-6.f);
    m_isInitialized = true;
}

sigrid::Color sigrid::TurnToken::getColor(const int& turnToMove) const{

    if(turnToMove == 1){
        sigrid::Color color;
        color.setRGB(0x000000);
        return color;
    }
    else{
        sigrid::Color color;
        color.setRGB(0xffffff);
        return color;
    }
}

void sigrid::TurnToken::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_isInitialized){
        return;
    }
    if(!m_isVisible){
        return;
    }
    target.draw(m_shape);
}