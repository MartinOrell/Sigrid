#include "Menu/MenuItem.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sigrid;

void MenuItem::createGraphic(const int height){
    
    if(m_text_o == std::nullopt){
        std::cerr << "MenuItem " << m_name << ": Failed creating graphic: missing text (most likely font is missing)" << std::endl;
        return;
    }
    auto& text = m_text_o.value();

    int characterSize = height-m_textOffset.y*2;

    text.setCharacterSize(characterSize);
    text.setFillColor(sf::Color(0,0,0));
    if(m_isToggled){
        text.setString(m_toggledName);
    }
    else{
        text.setString(m_name);
    }

    sf::FloatRect rect = text.getLocalBounds();
    text.setOrigin({0.f, (float)height/2.f+m_textOffset.y});

    int shapeWidth = rect.size.x+2*m_textOffset.x;
    m_shape.setSize({(float)shapeWidth,(float)height});

    m_shape.setOrigin({0.f, (float)height/2.f});
    m_shape.setOutlineColor(sf::Color(0,0,0));
    m_shape.setOutlineThickness(-2.f);
}

void MenuItem::setName(const std::string& name){
    m_name = name;
}

void MenuItem::setFont(const sf::Font& font){

    if(m_text_o == std::nullopt){
        m_text_o = sf::Text{font};
        return;
    }
    auto& text = m_text_o.value();

    text.setFont(font);
}

void MenuItem::setPosition(const sf::Vector2f& position){

    m_shape.setPosition(position);
    if(m_text_o == std::nullopt){
        return;
    }
    auto& text = m_text_o.value();

    text.setPosition({position.x + m_textOffset.x, position.y + m_textOffset.y});
}

void MenuItem::setAction(const sigrid_action::Action& action){
    m_action = action;
}

void MenuItem::setText(const std::string& s){
    
    if(m_text_o == std::nullopt){
        return;
    }
    auto& text = m_text_o.value();

    m_name = s;
    text.setString(s);
    sf::FloatRect rect = text.getLocalBounds();

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

sigrid_action::Action MenuItem::getAction(){

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

void MenuItem::addToggle(const std::string& name, const sigrid_action::Action& action){

    m_toggledName = name;
    m_toggledAction = action;
}

void MenuItem::toggle(){

    m_isToggled = !m_isToggled;

    if(m_text_o == std::nullopt){
        return;
    }
    auto& text = m_text_o.value();

    if(m_isToggled){
        text.setString(m_toggledName);
    }
    else{
        text.setString(m_name);
    }
    sf::FloatRect rect = text.getLocalBounds();
    
    float newHeight = m_shape.getSize().y;
    float newWidth = rect.size.x+2.f*m_textOffset.x;
    m_shape.setSize({newWidth, newHeight});
}

void MenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(m_shape);
    if(m_text_o != std::nullopt){
        auto& text = m_text_o.value();
        target.draw(text);
    }
}