#include "MenuItem.h"

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sigrid;

MenuItem::MenuItem(const std::string& name, const sf::Font& font, const Action action)
: m_name(name)
, m_action(action)
, m_text(font)
, m_textOffset({15.f,5.f})
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

    sf::FloatRect rect = m_text.getLocalBounds();
    m_text.setOrigin({0.f, (float)height/2.f+m_textOffset.y});

    unsigned int shapeWidth = rect.size.x+2*m_textOffset.x;
    m_shape.setSize({(float)shapeWidth,(float)height});

    m_shape.setOrigin({0.f, (float)height/2.f});
    m_shape.setOutlineColor(sf::Color(0,0,0));
    m_shape.setOutlineThickness(-2.f);
}

void MenuItem::setPosition(const sf::Vector2f& position){
    m_shape.setPosition(position);
    m_text.setPosition({position.x + m_textOffset.x, position.y + m_textOffset.y});
}

void MenuItem::setAction(const Action& action){
    m_action = action;
}

void MenuItem::setText(const std::string& text){
    
    m_name = text;
    m_text.setString(text);
    sf::FloatRect rect = m_text.getLocalBounds();

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

    if(m_isToggled){
        m_text.setString(m_toggledName);
    }
    else{
        m_text.setString(m_name);
    }
    sf::FloatRect rect = m_text.getLocalBounds();
    
    float newHeight = m_shape.getSize().y;
    float newWidth = rect.size.x+2.f*m_textOffset.x;
    m_shape.setSize({newWidth, newHeight});
}

void MenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_shape);
    target.draw(m_text);
}