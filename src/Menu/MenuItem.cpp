#include "MenuItem.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

using namespace sigrid;

MenuItem::MenuItem(std::string name, const sf::Font& font, const Action action)
: m_name(name)
, m_action(action)
, m_text(font)
, m_textOffset({15,2})
, m_isToggled{false}{}

void MenuItem::createGraphic(const unsigned int height){
    
    unsigned int characterSize = height-m_textOffset.y*2;

    m_text.setCharacterSize(characterSize);
    m_text.setFillColor(sf::Color(0,0,0));
    if(m_isToggled){
        m_text.setString(m_toggledName);
    }
    else{
        m_text.setString(m_name);
    }
    m_text.setScale({1.f,-1.f});

    sf::FloatRect rect = m_text.getLocalBounds();
    m_text.setOrigin({0.f, (float)height/2.f+(float)m_textOffset.y});

    unsigned int shapeWidth = rect.size.x+2*m_textOffset.x;
    m_shapePtr = std::make_unique<sf::RectangleShape>(sf::RectangleShape({(float)shapeWidth,(float)height}));

    m_shapePtr->setOrigin({0.f, (float)height/2.f});
    m_shapePtr->setOutlineColor(sf::Color(0,0,0));
    m_shapePtr->setOutlineThickness(-2.f);
}

void MenuItem::setPosition(sf::Vector2f position){
    m_shapePtr->setPosition(position);
    m_text.setPosition({position.x + m_textOffset.x, position.y + m_textOffset.y});
}

void MenuItem::setAction(const Action& action){
    m_action = action;
}

void MenuItem::setText(const std::string& text){
    
    m_name = text;
    m_text.setString(text);
    sf::FloatRect rect = m_text.getLocalBounds();

    float newHeight = m_shapePtr->getSize().y;
    float newWidth = rect.size.x+2.f*(float)m_textOffset.x;
    m_shapePtr->setSize({newWidth, newHeight});
}

float MenuItem::getPositionLeft(){
    return m_shapePtr->getPosition().x;
}

float MenuItem::getPositionRight(){
    return m_shapePtr->getPosition().x + m_shapePtr->getSize().x;
}

float MenuItem::getPositionTop(){
    return m_shapePtr->getPosition().y;
}

bool MenuItem::isWithin(sf::Vector2i point, float maxYPos, float minYPos){    

    if(point.x < m_shapePtr->getPosition().x){
        return false;
    }
    if(point.x > m_shapePtr->getPosition().x + m_shapePtr->getSize().x){
        return false;
    }

    //Unsure why, but y pos needs to be inverted

    float pointY = maxYPos+minYPos-point.y;

    if(pointY < m_shapePtr->getPosition().y - m_shapePtr->getSize().y/2.f){
        return false;
    }
    if(pointY > m_shapePtr->getPosition().y + m_shapePtr->getSize().y/2.f){
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

    if(m_isToggled){
        m_text.setString(m_toggledName);
    }
    else{
        m_text.setString(m_name);
    }
    sf::FloatRect rect = m_text.getLocalBounds();
    
    if(m_shapePtr){
        float newHeight = m_shapePtr->getSize().y;
        float newWidth = rect.size.x+2.f*(float)m_textOffset.x;
        m_shapePtr->setSize({newWidth, newHeight});
    }
}

void MenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*m_shapePtr);
    target.draw(m_text);
}