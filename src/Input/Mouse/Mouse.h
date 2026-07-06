#pragma once

#include <optional>
#include <functional> //Reference wrapper

#include <SFML/Window/Mouse.hpp>

#include "List/SigridMap.h"

namespace sigrid{
    class Mouse{
        public:
            Mouse();

            const std::optional<std::reference_wrapper<const sf::Vector2f>> getPressPosition(const sf::Mouse::Button& button) const;
            bool isPressed(const sf::Mouse::Button& button) const;

            void press(const sf::Mouse::Button& button, const sf::Vector2f& position);
            void release(const sf::Mouse::Button& button);

        private:
            list::SigridMap<sf::Mouse::Button, std::optional<sf::Vector2f>> m_pressedPositions;
    };
}

