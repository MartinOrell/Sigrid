#include "RectangleBorder.h"

using namespace sigrid;

#include <SFML/Graphics/RenderTarget.hpp>

#include <iostream>

RectangleBorder::RectangleBorder(){}

void RectangleBorder::setWidth(const unsigned int& width){
    m_width = width;
}

void RectangleBorder::setTopLeftPosition(const sf::Vector2f& topLeftPosition){
    m_topLeftPosition = topLeftPosition;
}

void RectangleBorder::setEnclosedArea(const sf::Vector2f& enclosedArea){
    m_enclosedArea = enclosedArea;
}

void RectangleBorder::init(const bool& isVisible){

    m_isVisible = isVisible;

    if(m_isVisible){
        initLeft();
        initRight();
        initTop();
        initBottom();
    }
}

RectangleBorder& RectangleBorder::operator =(const RectangleBorder& rhs){

    m_isVisible = rhs.m_isVisible;
    m_width = rhs.m_width;
    m_topLeftPosition = rhs.m_topLeftPosition;
    m_enclosedArea = rhs.m_enclosedArea;

    if(m_isVisible){
        initLeft();
        initRight();
        initTop();
        initBottom();
    }
    return *this;
}

bool RectangleBorder::isVisible() const{
    return m_isVisible;
}

bool RectangleBorder::isHidden() const{
    return !m_isVisible;
}

float RectangleBorder::getWidth() const{
    return (float)m_width;
}

void RectangleBorder::show(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea){
    m_isVisible = true;
    m_topLeftPosition = topLeftPosition;
    m_enclosedArea = enclosedArea;

    if(!m_left){
        initLeft();
    }

    if(!m_right){
        initRight();
    }

    if(!m_top){
        initTop();
    }

    if(!m_bottom){
        initBottom();
    }
}

void RectangleBorder::hide(){
    m_isVisible = false;
}

void RectangleBorder::addWidth(const float& addedWidth){

    if(m_right){
        m_right->move({addedWidth, 0.f});
    }
    if(m_top){
        m_top->setSize(m_top->getSize()+sf::Vector2f{addedWidth, 0.f});
    }
    if(m_bottom){
        m_bottom->setSize(m_bottom->getSize()+sf::Vector2f{addedWidth, 0.f});
    }
}

void RectangleBorder::addHeight(const float& addedHeight){

    if(m_left){
        m_left->setSize(m_left->getSize()+sf::Vector2f{0,addedHeight});
    }
    if(m_right){
        m_right->setSize(m_right->getSize()+sf::Vector2f{0,addedHeight});
        
    }
    if(m_bottom){
        m_bottom->move({0.f, addedHeight});
    }
}

void RectangleBorder::move(const sf::Vector2f& offset){

    m_topLeftPosition.x += offset.x;
    m_topLeftPosition.y += offset.y;

    if(m_left){
        m_left->move(offset);
    }

    if(m_right){
        m_right->move(offset);
    }

    if(m_top){
        m_top->move(offset);
    }

    if(m_bottom){
        m_bottom->move(offset);
    }
}

void RectangleBorder::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_isVisible){
        return;
    }

    if(m_left){
        target.draw(*m_left);
    }

    if(m_right){
        target.draw(*m_right);
    }

    if(m_top){
        target.draw(*m_top);
    }

    if(m_bottom){
        target.draw(*m_bottom);
    }
}

void RectangleBorder::initLeft(){

    if(m_width == 0){
        std::cerr << "RectangleBorder: Failed to init left border, border width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.x == 0.f){
        std::cerr << "RectangleBorder: Failed to init left border, enclosed area width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.y == 0.f){
        std::cerr << "RectangleBorder: Failed to init left border, enclosed area height is 0" << std::endl;
        return;
    }

    float width = (float)m_width;
    float height = m_enclosedArea.y + 2*m_width;
    m_left = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    m_left->setPosition(m_topLeftPosition);
    m_left->setFillColor(sf::Color{0,0,0,255});

}

void RectangleBorder::initRight(){

    if(m_width == 0){
        std::cerr << "RectangleBorder: Failed to init right border, border width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.x == 0.f){
        std::cerr << "RectangleBorder: Failed to init right border, enclosed area width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.y == 0.f){
        std::cerr << "RectangleBorder: Failed to init right border, enclosed area height is 0" << std::endl;
        return;
    }

    float width = (float)m_width;
    float height = m_enclosedArea.y + 2*m_width;
    m_right = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = m_topLeftPosition.x + m_enclosedArea.x + m_width;
    float y = m_topLeftPosition.y;
    m_right->setPosition({x,y});
    m_right->setFillColor(sf::Color{0,0,0,255});
}

void RectangleBorder::initTop(){

    if(m_width == 0){
        std::cerr << "RectangleBorder: Failed to init top border, border width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.x == 0.f){
        std::cerr << "RectangleBorder: Failed to init top border, enclosed area width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.y == 0.f){
        std::cerr << "RectangleBorder: Failed to init top border, enclosed area height is 0" << std::endl;
        return;
    }

    float width = m_enclosedArea.x + 2*m_width;
    float height = (float)m_width;
    m_top = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    m_top->setPosition(m_topLeftPosition);
    m_top->setFillColor(sf::Color{0,0,0,255});
}

void RectangleBorder::initBottom(){

    if(m_width == 0){
        std::cerr << "RectangleBorder: Failed to init bottom border, border width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.x == 0.f){
        std::cerr << "RectangleBorder: Failed to init bottom border, enclosed area width is 0" << std::endl;
        return;
    }

    if(m_enclosedArea.y == 0.f){
        std::cerr << "RectangleBorder: Failed to init bottom border, enclosed area height is 0" << std::endl;
        return;
    }

    float width = m_enclosedArea.x + 2*m_width;
    float height = (float)m_width;
    m_bottom = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = m_topLeftPosition.x;
    float y = m_topLeftPosition.y + m_enclosedArea.y + m_width;
    m_bottom->setPosition({x,y});
    m_bottom->setFillColor(sf::Color{0,0,0,255});
}

