#pragma once

#include <cstdint>

#include <SFML/Graphics/Color.hpp>

namespace sigrid{

struct Color{

    void setRGBA(const std::uint32_t& colorHex);
    
    std::uint32_t getRGBInteger() const;
    sf::Color getSfColor() const;
    sf::Color getSolidSfColor() const;

    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
    std::uint8_t a{255};

};

}  // namespace sigrid