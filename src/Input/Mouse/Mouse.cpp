#include "Mouse.h"

using namespace sigrid;

Mouse::Mouse(){

    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Left, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Right, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Middle, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Extra1, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Extra2, false});

    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Left, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Right, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Middle, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Extra1, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Extra2, {0,0}});
}

sf::Vector2f Mouse::getPressPosition(const sf::Mouse::Button& button) const{
    return m_mouseButtonPressedPositionMap.at(button);
}

bool Mouse::isPressed(const sf::Mouse::Button& button) const{
    return m_isMouseButtonPressedMap.at(button);
}

void Mouse::press(const sf::Mouse::Button& button, const sf::Vector2f& position){
 
    m_mouseButtonPressedPositionMap.at(button) = position;
    m_isMouseButtonPressedMap.at(button) = true;
}

void Mouse::release(const sf::Mouse::Button& button){

    m_isMouseButtonPressedMap.at(button) = false;
}