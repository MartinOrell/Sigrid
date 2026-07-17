#include "Entity/Shape/Circle/GraphicCircle.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sigrid;

void GraphicCircle::setPosition(const sf::Vector2f& position){
    m_shape.setPosition(position);
}

void GraphicCircle::setColor(const sf::Color& color){
    m_shape.setFillColor(color);
}

void GraphicCircle::setDiameter(const float& diameter){

    m_shape.setRadius(diameter/2.f);
    m_shape.setPointCount(100);
    m_shape.setOrigin(sf::Vector2f{diameter/2.f,diameter/2.f});
    m_shape.setOutlineColor(sf::Color::Black);
    
    float outlineThickness = diameter/10.f;
    if(outlineThickness < 2.f){
        outlineThickness = 2.f;
    }
    m_shape.setOutlineThickness(-outlineThickness);
}

void GraphicCircle::move(const sf::Vector2f& offset){
    m_shape.move(offset);
}

void GraphicCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}