#include "RectangleBorder.h"

using namespace sigrid;

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

RectangleBorder::RectangleBorder(){}

void RectangleBorder::setThickness(const float& thickness){

    m_thickness = thickness;

    //Left
    {
        float width = (float)m_thickness;
        float height = m_enclosedArea.y + 2*m_thickness;
        m_left.setSize(sf::Vector2f{width, height});
    }

    //Right
    {
        float width = (float)m_thickness;
        float height = m_enclosedArea.y + 2*m_thickness;
        m_right.setSize(sf::Vector2f{width, height});
        float x = m_topLeftPosition.x + m_enclosedArea.x + m_thickness;
        float y = m_topLeftPosition.y;
        m_right.setPosition({x,y});
    }

    //Top
    {
        float width = m_enclosedArea.x + 2*m_thickness;
        float height = (float)m_thickness;
        m_top.setSize(sf::Vector2f{width, height});
    }

    //Bottom
    {
        float width = m_enclosedArea.x + 2*m_thickness;
        float height = (float)m_thickness;
        m_bottom.setSize(sf::Vector2f{width, height});
        float x = m_topLeftPosition.x;
        float y = m_topLeftPosition.y + m_enclosedArea.y + m_thickness;
        m_bottom.setPosition({x,y});
    }
}

void RectangleBorder::setTopLeftPosition(const sf::Vector2f& topLeftPosition){

    m_topLeftPosition = topLeftPosition;

    //Left
    m_left.setPosition(topLeftPosition);

    //Right
    {
        float x = m_topLeftPosition.x + m_enclosedArea.x + m_thickness;
        float y = m_topLeftPosition.y;
        m_right.setPosition({x,y});
    }

    //Top
    m_top.setPosition(m_topLeftPosition);

    //Bottom
    {
        float x = m_topLeftPosition.x;
        float y = m_topLeftPosition.y + m_enclosedArea.y + m_thickness;
        m_bottom.setPosition({x,y});
    }
}

void RectangleBorder::setEnclosedArea(const sf::Vector2f& enclosedArea){
    
    m_enclosedArea = enclosedArea;

    //Left
    {
        float width = (float)m_thickness;
        float height = m_enclosedArea.y + 2*m_thickness;
        m_left.setSize(sf::Vector2f{width, height});
    }

    //Right
    {
        float width = (float)m_thickness;
        float height = m_enclosedArea.y + 2*m_thickness;
        m_right.setSize(sf::Vector2f{width, height});
        float x = m_topLeftPosition.x + m_enclosedArea.x + m_thickness;
        float y = m_topLeftPosition.y;
        m_right.setPosition({x,y});
    }

    //Top
    {
        float width = m_enclosedArea.x + 2*m_thickness;
        float height = (float)m_thickness;
        m_top.setSize(sf::Vector2f{width, height});
    }

    //Bottom
    {
        float width = m_enclosedArea.x + 2*m_thickness;
        float height = (float)m_thickness;
        m_bottom.setSize(sf::Vector2f{width, height});
        float x = m_topLeftPosition.x;
        float y = m_topLeftPosition.y + m_enclosedArea.y + m_thickness;
        m_bottom.setPosition({x,y});
    }
}

void RectangleBorder::setColor(const sf::Color& color){

    m_left.setFillColor(color);
    m_right.setFillColor(color);
    m_top.setFillColor(color);
    m_bottom.setFillColor(color);
}

RectangleBorder& RectangleBorder::operator =(const RectangleBorder& rhs){

    m_isVisible = rhs.m_isVisible;
    m_thickness = rhs.m_thickness;
    m_topLeftPosition = rhs.m_topLeftPosition;
    m_enclosedArea = rhs.m_enclosedArea;

    m_left.setSize(rhs.m_left.getSize());
    m_left.setPosition(rhs.m_left.getPosition());
    m_left.setFillColor(rhs.m_left.getFillColor());

    m_right.setSize(rhs.m_right.getSize());
    m_right.setPosition(rhs.m_right.getPosition());
    m_right.setFillColor(rhs.m_right.getFillColor());

    m_top.setSize(rhs.m_top.getSize());
    m_top.setPosition(rhs.m_top.getPosition());
    m_top.setFillColor(rhs.m_top.getFillColor());

    m_bottom.setSize(rhs.m_bottom.getSize());
    m_bottom.setPosition(rhs.m_bottom.getPosition());
    m_bottom.setFillColor(rhs.m_bottom.getFillColor());

    return *this;
}

bool RectangleBorder::isVisible() const{
    return m_isVisible;
}

bool RectangleBorder::isHidden() const{
    return !m_isVisible;
}

float RectangleBorder::getThickness() const{
    return (float)m_thickness;
}

void RectangleBorder::show(){
    m_isVisible = true;
}

void RectangleBorder::hide(){
    m_isVisible = false;
}

void RectangleBorder::addWidth(const float& addedWidth){

    m_right.move({addedWidth, 0.f});
    m_top.setSize(m_top.getSize()+sf::Vector2f{addedWidth, 0.f});
    m_bottom.setSize(m_bottom.getSize()+sf::Vector2f{addedWidth, 0.f});
}

void RectangleBorder::addHeight(const float& addedHeight){

    m_left.setSize(m_left.getSize()+sf::Vector2f{0,addedHeight});
    m_right.setSize(m_right.getSize()+sf::Vector2f{0,addedHeight});
    m_bottom.move({0.f, addedHeight});
}

void RectangleBorder::move(const sf::Vector2f& offset){

    m_topLeftPosition.x += offset.x;
    m_topLeftPosition.y += offset.y;

    m_left.move(offset);
    m_right.move(offset);
    m_top.move(offset);
    m_bottom.move(offset);
}

void RectangleBorder::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_isVisible){
        return;
    }

    target.draw(m_left);
    target.draw(m_right);
    target.draw(m_top);
    target.draw(m_bottom);
}