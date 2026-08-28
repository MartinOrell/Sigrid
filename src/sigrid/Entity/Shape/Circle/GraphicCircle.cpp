#include "sigrid/Entity/Shape/Circle/GraphicCircle.h"

#include <SFML/Graphics/RenderTarget.hpp>

void sigrid::GraphicCircle::setPosition(const sigrid::Position_f& position){
    m_shape.setPosition(position.getSfVector());
}

void sigrid::GraphicCircle::setColor(const sigrid::Color& color){
    m_shape.setFillColor(color.getSfColor());
}

void sigrid::GraphicCircle::setDiameter(const float& diameter){

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

void sigrid::GraphicCircle::move(const sigrid::Offset_f& offset){
    m_shape.move(offset.getSfVector());
}

void sigrid::GraphicCircle::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
}