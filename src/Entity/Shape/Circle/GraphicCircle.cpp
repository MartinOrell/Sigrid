#include "Entity/Shape/Circle/GraphicCircle.h"

#include <SFML/Graphics/RenderTarget.hpp>

using namespace sigrid;

GraphicCircle::GraphicCircle(const sf::Color& color, const float& diameter)
: m_shape(diameter/2.f, 100){
    m_shape.setOrigin(sf::Vector2f{diameter/2.f,diameter/2.f});
    m_shape.setFillColor(color);
    m_shape.setOutlineColor(sf::Color::Black);
    
    float outlineThickness = diameter/10.f;
    if(outlineThickness < 2.f){
        outlineThickness = 2.f;
    }
    m_shape.setOutlineThickness(-outlineThickness);
}

GraphicCircle::GraphicCircle(const GraphicCircle& src){
    m_shape = src.m_shape;
}

GraphicCircle& GraphicCircle::operator =(const GraphicCircle& src){
    m_shape = src.m_shape;
    return *this;
}

void GraphicCircle::setPosition(const sf::Vector2f& position){
    m_shape.setPosition(position);
}

void GraphicCircle::setColor(const sf::Color& color){
    m_shape.setFillColor(color);
}

void GraphicCircle::move(const sf::Vector2f& offset){
    m_shape.move(offset);
}

void GraphicCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}