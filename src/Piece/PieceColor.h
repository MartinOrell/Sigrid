#pragma once

#include <SFML/Graphics/Color.hpp>

namespace sigrid{
    struct PieceColor{
        bool isLight;
        sf::Color lightModifier;
        sf::Color darkModifier;
    };
}
