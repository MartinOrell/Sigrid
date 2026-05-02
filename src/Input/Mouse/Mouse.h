#pragma once

#include <map>
#include <SFML/Window/Mouse.hpp>

namespace sigrid{
    class Mouse{
        public:
            Mouse();

            sf::Vector2f getPressPosition(const sf::Mouse::Button& button) const;
            bool isPressed(const sf::Mouse::Button& button) const;

            void press(const sf::Mouse::Button& button, const sf::Vector2f& position);
            void release(const sf::Mouse::Button& button);

        private:
            std::map<sf::Mouse::Button, bool> m_isMouseButtonPressedMap;
            std::map<sf::Mouse::Button, sf::Vector2f> m_mouseButtonPressedPositionMap;
    };
}

