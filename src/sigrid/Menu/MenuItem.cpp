#include "sigrid/Menu/MenuItem.h"

#include <iostream>

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

sigrid::MenuItemContainer sigrid::MenuItem::getContainer() const{

    if(m_toggledName == ""){
        MenuItemContainer container;
        container.displayNames.push_back(m_name);
        container.actionNames.push_back(sigrid_action::getString(m_action));
        return container;
    }

    if(!m_isToggled){
        MenuItemContainer container;
        container.displayNames.push_back(m_name);
        container.displayNames.push_back(m_toggledName);
        container.actionNames.push_back(sigrid_action::getString(m_action));
        container.actionNames.push_back(sigrid_action::getString(m_toggledAction));
        return container;
    }

    MenuItemContainer container;
    container.displayNames.push_back(m_toggledName);
    container.displayNames.push_back(m_name);
    container.actionNames.push_back(sigrid_action::getString(m_toggledAction));
    container.actionNames.push_back(sigrid_action::getString(m_action));

    return container;
}

void sigrid::MenuItem::createGraphic(const int height){
    
    if(!m_text.isInitialized()){
        std::cerr << "MenuItem " << m_name
            << ": Failed to create graphic."
            << " text is not initialized (most likely font is missing)" << std::endl;
        return;
    }

    int characterSize = height-m_textOffset.y*2;

    m_text.setCharacterSize(characterSize);

    sigrid::Color fillColor;
    fillColor.setRGB(0x000000);
    m_text.setFillColor(fillColor);
    if(m_isToggled){
        m_text.setString(m_toggledName);
    }
    else{
        m_text.setString(m_name);
    }

    m_text.setOrigin({0.f, (float)height/2.f+m_textOffset.y});

    int shapeWidth = m_text.getLocalWidth()+2*m_textOffset.x;
    m_shape.setSize({(float)shapeWidth,(float)height});

    m_shape.setOrigin({0.f, (float)height/2.f});
    m_shape.setOutlineColor(sf::Color(0,0,0));
    m_shape.setOutlineThickness(-2.f);
}

void sigrid::MenuItem::setName(const sigrid::String& name){
    m_name = name;
}

void sigrid::MenuItem::setFont(const sf::Font& font){
    m_text.setFont(font);
}

void sigrid::MenuItem::setPosition(const sf::Vector2f& position){

    m_shape.setPosition(position);

    if(m_text.isInitialized()){
        m_text.setPosition({position.x + m_textOffset.x, position.y + m_textOffset.y});
    }
}

void sigrid::MenuItem::setAction(const sigrid_action::Action& action){
    m_action = action;
}

void sigrid::MenuItem::setText(const sigrid::String& s){
    
    if(!m_text.isInitialized()){
        return;
    }

    m_name = s;
    m_text.setString(s);

    float newHeight = m_shape.getSize().y;
    float newWidth = m_text.getLocalWidth()+2.f*m_textOffset.x;
    m_shape.setSize({newWidth, newHeight});
}

float sigrid::MenuItem::getPositionLeft() const{
    return m_shape.getPosition().x;
}

float sigrid::MenuItem::getPositionRight() const{
    return m_shape.getPosition().x + m_shape.getSize().x;
}

float sigrid::MenuItem::getPositionTop() const{
    return m_shape.getPosition().y;
}

bool sigrid::MenuItem::isWithin(const sf::Vector2f& point, const float& maxYPos, const float& minYPos) const{

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

sigrid_action::Action sigrid::MenuItem::getAction() const{

    if(m_isToggled){
        return m_toggledAction;
    }
    return m_action;
}

sigrid::String sigrid::MenuItem::getName() const{

    if(m_isToggled){
        return m_toggledName;
    }
    return m_name;
}

void sigrid::MenuItem::addToggle(const sigrid::String& name, const sigrid_action::Action& action){

    m_toggledName = name;
    m_toggledAction = action;
}

void sigrid::MenuItem::toggle(){

    m_isToggled = !m_isToggled;

    if(!m_text.isInitialized()){
        return;
    }

    if(m_isToggled){
        m_text.setString(m_toggledName);
    }
    else{
        m_text.setString(m_name);
    }
    
    float newHeight = m_shape.getSize().y;
    float newWidth = m_text.getLocalWidth()+2.f*m_textOffset.x;
    m_shape.setSize({newWidth, newHeight});
}

void sigrid::MenuItem::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    target.draw(m_shape);
    target.draw(m_text);
}