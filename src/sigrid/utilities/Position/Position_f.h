#pragma once

#include <SFML/System/Vector2.hpp>

namespace sigrid{

struct Position_f{

    sf::Vector2<float> getSfPosition() const;

    Position_f operator+(const Position_f& rhs) const;
    Position_f operator-(const Position_f& rhs) const;
    Position_f operator*(const float& rhs) const;
    Position_f operator/(const float& rhs) const;

    void set(const sf::Vector2f& sfVector);

    float x;
    float y;
};

}  // namespace sigrid