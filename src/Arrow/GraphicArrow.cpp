#include "GraphicArrow.h"

#include <iostream>

using namespace sigrid;

GraphicArrow::GraphicArrow(sf::Vector2f fromPosition, sf::Vector2f toPosition, sf::Color color){

    float thickness = 5.f;
    float headSize = 15.f;

    m_line.setFillColor(color);
    m_line.setOrigin({0, thickness/2.f});
    m_head.setFillColor(color);
    m_head.setRadius(headSize);
    m_head.setPointCount(3);
    m_head.setOrigin({headSize, headSize});
    
    m_line.setPosition(fromPosition);

    float x = toPosition.x - fromPosition.x;
    float y = toPosition.y - fromPosition.y;
    float length = sqrt(x*x+y*y);

    //Set points for line with rounded edge
    const unsigned int precision{ (unsigned int)(thickness * 2)};

    m_line.setPointCount(precision + 2);
    size_t index{0};
    m_line.setPoint(index, sf::Vector2f(0.f,0.f)); //start of line
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f+length - headSize * 3.f /2.f, 0.f)); //to head
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f + length - headSize *3.f / 2.f, thickness)); //to head 2
    index++;
    m_line.setPoint(index, sf::Vector2f(0.f, thickness));

    //rounded edge
    for(unsigned int i = 1; i < precision - 1; i++){
        float radius = ((float)i / (float) precision * 3.14f);
        float posX = (-sin(radius)) * thickness / 2.f;
        float posY = thickness - (1.f - cos(radius)) * thickness / 2.f;
        m_line.setPoint(index, {posX,posY});
        index++;
    }

    float rotation = atan2(y, x);

    m_line.setRotation(sf::radians(rotation));
    m_head.setRotation(sf::radians(3.14f/2.f + rotation));
    
    sf::Vector2f headPosition;
    headPosition.x = fromPosition.x + (cos(rotation)) * (length - headSize);
    headPosition.y = fromPosition.y + (sin(rotation)) * (length - headSize);

    m_head.setPosition(headPosition);
}

GraphicArrow::GraphicArrow(const GraphicArrow& src){
    m_line = src.m_line;
    m_head = src.m_head;
}

GraphicArrow& GraphicArrow::operator =(const GraphicArrow& src){
    m_line = src.m_line;
    m_head = src.m_head;
    return *this;
}

void GraphicArrow::set(const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition){
    float thickness = 5.f;
    float headSize = 15.f;
    const unsigned int precision{ (unsigned int)(thickness * 2)};

    m_line.setPosition(fromPosition);

    float x = toPosition.x - fromPosition.x;
    float y = toPosition.y - fromPosition.y;
    float length = sqrt(x*x+y*y);

    size_t index{0};
    m_line.setPoint(index, sf::Vector2f(0.f,0.f)); //start of line
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f+length - headSize * 3.f /2.f, 0.f)); //to head
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f + length - headSize *3.f / 2.f, thickness)); //to head 2
    index++;
    m_line.setPoint(index, sf::Vector2f(0.f, thickness));

    //rounded edge
    for(unsigned int i = 1; i < precision - 1; i++){
        float radius = ((float)i / (float) precision * 3.14f);
        float posX = (-sin(radius)) * thickness / 2.f;
        float posY = thickness - (1.f - cos(radius)) * thickness / 2.f;
        m_line.setPoint(index, {posX,posY});
        index++;
    }

    float rotation = atan2(y, x);

    m_line.setRotation(sf::radians(rotation));
    m_head.setRotation(sf::radians(3.14f/2.f + rotation));
    
    sf::Vector2f headPosition;
    headPosition.x = fromPosition.x + (cos(rotation)) * (length - headSize);
    headPosition.y = fromPosition.y + (sin(rotation)) * (length - headSize);

    m_head.setPosition(headPosition);
}

void GraphicArrow::setColor(sf::Color color){
    m_line.setFillColor(color);
    m_head.setFillColor(color);
}

void GraphicArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_line);
    target.draw(m_head);
}