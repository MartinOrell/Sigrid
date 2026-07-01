#include "MenuItem.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sigrid;

MenuItem::MenuItem(){}

MenuItem::MenuItem(const MenuItem& src){
    *this = src;
}

MenuItem& MenuItem::operator=(const MenuItem& rhs){

    m_name = rhs.m_name;
    m_shape = rhs.m_shape;
    m_action = rhs.m_action;

    if(rhs.m_textPtr){
        if(!m_textPtr){
            m_textPtr = std::make_unique<sf::Text>(*(rhs.m_textPtr));
        }
        else{
            *m_textPtr = *(rhs.m_textPtr);
        }
    }

    m_textOffset = rhs.m_textOffset;
    m_isToggled = rhs.m_isToggled;
    m_toggledName = rhs.m_toggledName;
    m_toggledAction = rhs.m_toggledAction;

    return *this;
}

void MenuItem::createGraphic(const unsigned int height){
    
    if(!m_textPtr){
        std::cerr << "MenuItem " << m_name << ": Failed creating graphic: missing textPtr (most likely font is missing)" << std::endl;
        return;
    }

    unsigned int characterSize = height-m_textOffset.y*2;

    m_textPtr->setCharacterSize(characterSize);
    m_textPtr->setFillColor(sf::Color(0,0,0));
    if(m_isToggled){
        m_textPtr->setString(m_toggledName);
    }
    else{
        m_textPtr->setString(m_name);
    }

    sf::FloatRect rect = m_textPtr->getLocalBounds();
    m_textPtr->setOrigin({0.f, (float)height/2.f+m_textOffset.y});

    unsigned int shapeWidth = rect.size.x+2*m_textOffset.x;
    m_shape.setSize({(float)shapeWidth,(float)height});

    m_shape.setOrigin({0.f, (float)height/2.f});
    m_shape.setOutlineColor(sf::Color(0,0,0));
    m_shape.setOutlineThickness(-2.f);
}

void MenuItem::setName(const std::string& name){
    m_name = name;
}

void MenuItem::setFont(const sf::Font& font){

    if(!m_textPtr){
        m_textPtr = std::make_unique<sf::Text>(font);
        return;
    }

    m_textPtr->setFont(font);
}

void MenuItem::setPosition(const sf::Vector2f& position){
    m_shape.setPosition(position);
    if(m_textPtr){
        m_textPtr->setPosition({position.x + m_textOffset.x, position.y + m_textOffset.y});
    }
}

void MenuItem::setAction(const Action& action){
    m_action = action;
}

void MenuItem::setText(const std::string& text){
    
    if(!m_textPtr){
        return;
    }

    m_name = text;
    m_textPtr->setString(text);
    sf::FloatRect rect = m_textPtr->getLocalBounds();

    float newHeight = m_shape.getSize().y;
    float newWidth = rect.size.x+2.f*m_textOffset.x;
    m_shape.setSize({newWidth, newHeight});
}

float MenuItem::getPositionLeft(){
    return m_shape.getPosition().x;
}

float MenuItem::getPositionRight(){
    return m_shape.getPosition().x + m_shape.getSize().x;
}

float MenuItem::getPositionTop(){
    return m_shape.getPosition().y;
}

bool MenuItem::isWithin(const sf::Vector2f& point, const float& maxYPos, const float& minYPos){    

    if(point.x < m_shape.getPosition().x){
        return false;
    }
    if(point.x > m_shape.getPosition().x + m_shape.getSize().x){
        return false;
    }

    if(point.y < m_shape.getPosition().y - m_shape.getSize().y/2.f){
        return false;
    }
    if(point.y > m_shape.getPosition().y + m_shape.getSize().y/2.f){
        return false;
    }
    return true;
}

Action MenuItem::getAction(){
    if(m_isToggled){
        return m_toggledAction;
    }
    return m_action;
}

std::string MenuItem::getName(){
    if(m_isToggled){
        return m_toggledName;
    }
    return m_name;
}

void MenuItem::addToggle(const std::string& name, const Action& action){
    m_toggledName = name;
    m_toggledAction = action;
}

void MenuItem::toggle(){
    m_isToggled = !m_isToggled;

    if(!m_textPtr){
        return;
    }

    if(m_isToggled){
        m_textPtr->setString(m_toggledName);
    }
    else{
        m_textPtr->setString(m_name);
    }
    sf::FloatRect rect = m_textPtr->getLocalBounds();
    
    float newHeight = m_shape.getSize().y;
    float newWidth = rect.size.x+2.f*m_textOffset.x;
    m_shape.setSize({newWidth, newHeight});
}

void MenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
    if(m_textPtr){
        target.draw(*m_textPtr);
    }
}