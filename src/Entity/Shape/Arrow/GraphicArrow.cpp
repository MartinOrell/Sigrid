#include "GraphicArrow.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

using namespace sigrid;

GraphicArrow::GraphicArrow(){}

void GraphicArrow::setFromPosition(const sf::Vector2f& fromPosition){
    m_line.setPosition(fromPosition);
}

void GraphicArrow::setToPosition(const sf::Vector2f& toPosition){
    m_toPosition = toPosition;
}

void GraphicArrow::setColor(const sf::Color& color){
    m_line.setFillColor(color);
    m_head.setFillColor(color);
}

void GraphicArrow::setThickness(const float& thickness){
    m_thickness = thickness;
}

void GraphicArrow::setHeadSize(const float& size){
    m_headSize = size;
}

void GraphicArrow::init(){

    if(m_thickness == 0.f){
        std::cerr << "GraphicArrow: init failed, thickness is 0" << std::endl;
        return;
    }
    
    if(m_headSize == 0.f){
        std::cerr << "GraphicArrow: init failed, head size is 0" << std::endl;
        return;
    }
    
    m_line.setOrigin({0, m_thickness/2.f});
    m_head.setRadius(m_headSize);
    m_head.setPointCount(3);
    m_head.setOrigin({m_headSize, m_headSize});

    sf::Vector2f fromPosition = m_line.getPosition();

    float x = m_toPosition.x - fromPosition.x;
    float y = m_toPosition.y - fromPosition.y;
    float length = sqrt(x*x+y*y);

    //Set points for line with rounded edge
    const unsigned int precision{ (unsigned int)(m_thickness * 2)};

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
    for(unsigned int i = 1; i < precision - 1; i++){
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

GraphicArrow& GraphicArrow::operator =(const GraphicArrow& src){
    m_line = src.m_line;
    m_head = src.m_head;
    m_thickness = src.m_thickness;
    m_headSize = src.m_headSize;
    m_toPosition = src.m_toPosition;
    return *this;
}

void GraphicArrow::set(const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition){

    if(m_thickness == 0.f){
        std::cerr << "GraphicArrow: set failed, thickness is 0" << std::endl;
        return;
    }
    
    if(m_headSize == 0.f){
        std::cerr << "GraphicArrow: set failed, head size is 0" << std::endl;
        return;
    }

    m_toPosition = toPosition;

    const unsigned int precision{ (unsigned int)(m_thickness * 2)};

    m_line.setPosition(fromPosition);

    float x = toPosition.x - fromPosition.x;
    float y = toPosition.y - fromPosition.y;
    float length = sqrt(x*x+y*y);

    size_t index{0};
    m_line.setPoint(index, sf::Vector2f(0.f,0.f)); //start of line
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f+length - m_headSize * 3.f /2.f, 0.f)); //to head
    index++;
    m_line.setPoint(index, sf::Vector2f(1.f + length - m_headSize *3.f / 2.f, m_thickness)); //to head 2
    index++;
    m_line.setPoint(index, sf::Vector2f(0.f, m_thickness));

    //rounded edge
    for(unsigned int i = 1; i < precision - 1; i++){
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

void GraphicArrow::setPosition(const sf::Vector2f& position){
    sf::Vector2f offset = position - m_line.getPosition();
    move(offset);
}

void GraphicArrow::move(const sf::Vector2f& offset){
    m_line.move(offset);
    m_head.move(offset);
}

void GraphicArrow::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_line);
    target.draw(m_head);
}