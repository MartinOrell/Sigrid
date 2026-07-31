#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace sf{
    template <typename T> class Vector2;
    using Vector2f = Vector2<float>;
    class Color;
}

namespace sigrid{

class TurnToken: public sf::Drawable{

  public:

    TurnToken() = default;
    TurnToken(const TurnToken&) = default;
    TurnToken(TurnToken&&) = default;
    TurnToken& operator=(const TurnToken&) = default;
    TurnToken& operator=(TurnToken&&) = default;

    void setRadius(const float& radius);

    void setCenterPosition(const sf::Vector2f& centerPosition);

    void setTurnToMove(const int& turnToMove);

    bool isVisible() const;
    bool isHidden() const;

    bool isWithin(const sf::Vector2f& point) const;

    float getRadius() const;

    sf::Vector2f getCenterPosition() const;

    void show();

    void hide();

    void move(const sf::Vector2f& offset);

  private:

    bool m_isInitialized = false;
    void init();

    sf::Color getColor(const int& turnToMove) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool m_isVisible = false;
    sf::CircleShape m_shape;
};

}  // namespace sigrid