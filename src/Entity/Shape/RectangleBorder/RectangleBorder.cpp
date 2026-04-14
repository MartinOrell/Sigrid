#include "RectangleBorder.h"

using namespace sigrid;

#include <SFML/Graphics/RenderTarget.hpp>

RectangleBorder::RectangleBorder(){}

void RectangleBorder::init(const bool& isVisible, const unsigned int& width, const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea){

    m_isVisible = isVisible;
    m_width = width;

    if(m_isVisible){
        initLeft(topLeftPosition, enclosedArea);
        initRight(topLeftPosition, enclosedArea);
        initTop(topLeftPosition, enclosedArea);
        initBottom(topLeftPosition, enclosedArea);
    }
}

RectangleBorder& RectangleBorder::operator =(const RectangleBorder& rhs){

    m_isVisible = rhs.m_isVisible;
    m_width = rhs.m_width;

    if(!rhs.m_left){
        return *this;
    }

    if(!rhs.m_top){
        return *this;
    }

    sf::Vector2f topLeftPosition = rhs.m_left->getPosition();
    sf::Vector2f enclosedArea;
    enclosedArea.x = rhs.m_top->getSize().x - 2*m_width;
    enclosedArea.y = rhs.m_left->getSize().y - 2*m_width;

    if(m_isVisible){
        initLeft(topLeftPosition, enclosedArea);
        initRight(topLeftPosition, enclosedArea);
        initTop(topLeftPosition, enclosedArea);
        initBottom(topLeftPosition, enclosedArea);
    }
    return *this;
}

bool RectangleBorder::isVisible() const{
    return m_isVisible;
}

float RectangleBorder::getWidth() const{
    return (float)m_width;
}

void RectangleBorder::show(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea){
    m_isVisible = true;

    if(!m_left){
        initLeft(topLeftPosition, enclosedArea);
    }

    if(!m_right){
        initRight(topLeftPosition, enclosedArea);
    }

    if(!m_top){
        initTop(topLeftPosition, enclosedArea);
    }

    if(!m_bottom){
        initBottom(topLeftPosition, enclosedArea);
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

void RectangleBorder::initLeft(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea){

    float width = (float)m_width;
    float height = enclosedArea.y + 2*m_width;
    m_left = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    m_left->setPosition(topLeftPosition);
    m_left->setFillColor(sf::Color{0,0,0,255});

}

void RectangleBorder::initRight(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea){

    float width = (float)m_width;
    float height = enclosedArea.y + 2*m_width;
    m_right = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = topLeftPosition.x + enclosedArea.x + m_width;
    float y = topLeftPosition.y;
    m_right->setPosition({x,y});
    m_right->setFillColor(sf::Color{0,0,0,255});
}

void RectangleBorder::initTop(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea){

    float width = enclosedArea.x + 2*m_width;
    float height = (float)m_width;
    m_top = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    m_top->setPosition(topLeftPosition);
    m_top->setFillColor(sf::Color{0,0,0,255});
}

void RectangleBorder::initBottom(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea){

    float width = enclosedArea.x + 2*m_width;
    float height = (float)m_width;
    m_bottom = std::make_unique<sf::RectangleShape>(sf::Vector2f{width, height});
    float x = topLeftPosition.x;
    float y = topLeftPosition.y + enclosedArea.y + m_width;
    m_bottom->setPosition({x,y});
    m_bottom->setFillColor(sf::Color{0,0,0,255});
}

