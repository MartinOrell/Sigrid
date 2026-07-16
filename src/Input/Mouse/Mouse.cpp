#include "Input/Mouse/Mouse.h"

using namespace sigrid;

const std::optional<std::reference_wrapper<const sf::Vector2f>> Mouse::getPressPosition(const sf::Mouse::Button& button) const{
    
    auto position_o = m_pressedPositions.at(button);

    if(position_o == std::nullopt){
        return std::nullopt;
    }
    return position_o.value().get();
}

bool Mouse::isPressed(const sf::Mouse::Button& button) const{
    return m_pressedPositions.at(button) != std::nullopt;
}

void Mouse::press(const sf::Mouse::Button& button, const sf::Vector2f& pressPosition){
 
    auto mappedPosition_o = m_pressedPositions.at(button);

    if(mappedPosition_o == std::nullopt){
        m_pressedPositions.insert(button, pressPosition);
        return;
    }
    auto& mappedPosition = mappedPosition_o.value().get();
    mappedPosition = pressPosition;
}

void Mouse::release(const sf::Mouse::Button& button){

    auto position_o = m_pressedPositions.at(button);

    if(position_o == std::nullopt){
        return;
    }
    auto& position = position_o.value().get();
    position = std::nullopt;
}