#include "sigrid/Entity/Shape/Arrow/GraphicArrow.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

void sigrid::GraphicArrow::setFromPosition(const sigrid::Position_f& fromPosition){
    
    m_line.setPosition(fromPosition.getSfVector());
    m_isSet.fromPosition = true;
    if(m_isSet.isAllSet()){
        updateShape();
    }
}

void sigrid::GraphicArrow::setToPosition(const sigrid::Position_f& toPosition){
    
    m_toPosition = toPosition;
    m_isSet.toPosition = true;
    if(m_isSet.isAllSet()){
        updateShape();
    }
}

void sigrid::GraphicArrow::setPosition(const sigrid::Position_f& fromPosition, const sigrid::Position_f& toPosition){
    
    m_line.setPosition(fromPosition.getSfVector());
    m_toPosition = toPosition;
    m_isSet.fromPosition = true;
    m_isSet.toPosition = true;
    if(m_isSet.isAllSet()){
        updateShape();
    }
}

void sigrid::GraphicArrow::setColor(const sigrid::Color& color){

    m_line.setFillColor(color.getSfColor());
    m_head.setFillColor(color.getSfColor());
}

void sigrid::GraphicArrow::setThickness(const float& thickness){
    
    m_thickness = thickness;
    if(m_thickness <= 0.f){
        return;
    }
    m_isSet.thickness = true;
    if(m_isSet.isAllSet()){
        updateShape();
    }
}

void sigrid::GraphicArrow::setHeadSize(const float& size){
    
    m_headSize = size;
    if(m_headSize <= 0.f){
        return;
    }
    m_isSet.headSize = true;
    if(m_isSet.isAllSet()){
        updateShape();
    }
}

void sigrid::GraphicArrow::setPosition(const sigrid::Position_f& position){
    
    sigrid::Position_f oldPosition;
    oldPosition.set(m_line.getPosition());
    move(position - oldPosition);
}

void sigrid::GraphicArrow::move(const sigrid::Offset_f& offset){
    
    m_line.move(offset.getSfVector());
    m_head.move(offset.getSfVector());
}

bool sigrid::GraphicArrow::IsSet::isAllSet(){
    
    return fromPosition &&
        toPosition &&
        thickness &&
        headSize;
}

void sigrid::GraphicArrow::updateShape(){

    m_line.setOrigin({0, m_thickness/2.f});
    m_head.setRadius(m_headSize);
    m_head.setPointCount(3);
    m_head.setOrigin({m_headSize, m_headSize});

    sf::Vector2f fromPosition = m_line.getPosition();

    float x = m_toPosition.x - fromPosition.x;
    float y = m_toPosition.y - fromPosition.y;
    float length = sqrt(x*x+y*y);

    //Set points for line with rounded edge
    const int precision{ (int)(m_thickness * 2)};

    m_line.setPointCount(precision + 2);
    size_t index{0};
    m_line.setPoint(index, sf::Vector2f(0.f,0.f)); //start of line
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f+length - m_headSize * 3.f /2.f, 0.f)); //to head
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f + length - m_headSize *3.f / 2.f, m_thickness)); //to head 2
    index++;
    m_line.setPoint(index, sf::Vector2f(0.f, m_thickness));

    //rounded edge
    for(int i = 1; i < precision - 1; i++){
        float radius = ((float)i / (float) precision * 3.14f);
        float posX = (-sin(radius)) * m_thickness / 2.f;
        float posY = m_thickness - (1.f - cos(radius)) * m_thickness / 2.f;
        m_line.setPoint(index, {posX,posY});
        index++;
    }

    float rotation = atan2(y, x);

    m_line.setRotation(sf::radians(rotation));
    m_head.setRotation(sf::radians(3.14f/2.f + rotation));
    
    sf::Vector2f headPosition;
    headPosition.x = fromPosition.x + (cos(rotation)) * (length - m_headSize);
    headPosition.y = fromPosition.y + (sin(rotation)) * (length - m_headSize);

    m_head.setPosition(headPosition);
}

void sigrid::GraphicArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    
    target.draw(m_line);
    target.draw(m_head);
}