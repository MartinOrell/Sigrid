#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorder.h"

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

sigrid::RectangleBorderContainer sigrid::RectangleBorder::getContainer() const{

    RectangleBorderContainer container;
    container.isVisible = this->m_isVisible;
    container.thickness = this->m_thickness;

    return container;
}

void sigrid::RectangleBorder::setThickness(const float& thickness){

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

void sigrid::RectangleBorder::setTopLeftPosition(const sigrid::Position_f& topLeftPosition){

    m_topLeftPosition = topLeftPosition;

    //Left
    m_left.setPosition(topLeftPosition.getSfPosition());

    //Right
    {
        float x = m_topLeftPosition.x + m_enclosedArea.x + m_thickness;
        float y = m_topLeftPosition.y;
        m_right.setPosition({x,y});
    }

    //Top
    m_top.setPosition(m_topLeftPosition.getSfPosition());

    //Bottom
    {
        float x = m_topLeftPosition.x;
        float y = m_topLeftPosition.y + m_enclosedArea.y + m_thickness;
        m_bottom.setPosition({x,y});
    }
}

void sigrid::RectangleBorder::setEnclosedArea(const sigrid::Size_f& enclosedArea){
    
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

void sigrid::RectangleBorder::setColor(const sigrid::Color& color){

    m_left.setFillColor(color.getSfColor());
    m_right.setFillColor(color.getSfColor());
    m_top.setFillColor(color.getSfColor());
    m_bottom.setFillColor(color.getSfColor());
}

bool sigrid::RectangleBorder::isVisible() const{
    return m_isVisible;
}

bool sigrid::RectangleBorder::isHidden() const{
    return !m_isVisible;
}

float sigrid::RectangleBorder::getThickness() const{
    return (float)m_thickness;
}

void sigrid::RectangleBorder::show(){
    m_isVisible = true;
}

void sigrid::RectangleBorder::hide(){
    m_isVisible = false;
}

void sigrid::RectangleBorder::addWidth(const float& addedWidth){

    m_right.move({addedWidth, 0.f});
    m_top.setSize(m_top.getSize()+sf::Vector2f{addedWidth, 0.f});
    m_bottom.setSize(m_bottom.getSize()+sf::Vector2f{addedWidth, 0.f});
}

void sigrid::RectangleBorder::addHeight(const float& addedHeight){

    m_left.setSize(m_left.getSize()+sf::Vector2f{0,addedHeight});
    m_right.setSize(m_right.getSize()+sf::Vector2f{0,addedHeight});
    m_bottom.move({0.f, addedHeight});
}

void sigrid::RectangleBorder::move(const sf::Vector2f& offset){

    m_topLeftPosition.x += offset.x;
    m_topLeftPosition.y += offset.y;

    m_left.move(offset);
    m_right.move(offset);
    m_top.move(offset);
    m_bottom.move(offset);
}

void sigrid::RectangleBorder::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_isVisible){
        return;
    }

    target.draw(m_left);
    target.draw(m_right);
    target.draw(m_top);
    target.draw(m_bottom);
}