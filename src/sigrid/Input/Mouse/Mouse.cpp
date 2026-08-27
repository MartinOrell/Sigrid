#include "sigrid/Input/Mouse/Mouse.h"

const std::optional<std::reference_wrapper<const sigrid::Position_f>> sigrid::Mouse::getPressPosition(const sf::Mouse::Button& button) const{
    
    auto position_o = m_pressedPositions.at(button);

    if(position_o == std::nullopt){
        return std::nullopt;
    }
    return position_o.value().get();
}

bool sigrid::Mouse::isPressed(const sf::Mouse::Button& button) const{
    return m_pressedPositions.at(button) != std::nullopt;
}

void sigrid::Mouse::press(const sf::Mouse::Button& button, const sigrid::Position_f& pressPosition){
 
    auto mappedPosition_o = m_pressedPositions.at(button);

    if(mappedPosition_o == std::nullopt){
        m_pressedPositions.insert(button, pressPosition);
        return;
    }
    auto& mappedPosition = mappedPosition_o.value().get();
    mappedPosition = pressPosition;
}

void sigrid::Mouse::release(const sf::Mouse::Button& button){

    auto position_o = m_pressedPositions.at(button);

    if(position_o == std::nullopt){
        return;
    }
    auto& position = position_o.value().get();
    position = std::nullopt;
}