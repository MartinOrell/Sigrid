#pragma once

#include <cstdint>

#include <SFML/Graphics/Color.hpp>

#include "sigrid/utilities/String/String.h"

namespace sigrid{

struct Color{

    void setRGB(const std::uint32_t& rgb);
    void setRGBA(const std::uint32_t& rgba);
    
    std::uint32_t getRGBInteger() const;
    sigrid::String getRGBString() const;
    sf::Color getSfColor() const;
    sf::Color getSolidSfColor() const;

    std::uint8_t r{};
    std::uint8_t g{};
    std::uint8_t b{};
    std::uint8_t a{255};

};

}  // namespace sigrid