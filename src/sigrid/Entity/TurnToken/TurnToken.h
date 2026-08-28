#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Offset/Offset_f.h"
#include "sigrid/Entity/TurnToken/TurnTokenContainer.h"
#include "sigrid/utilities/Color/Color.h"

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

    TurnTokenContainer getContainer() const;

    void setRadius(const float& radius);

    void setCenterPosition(const sigrid::Position_f& centerPosition);

    void setTurnToMove(const int& turnToMove);

    bool isVisible() const;
    bool isHidden() const;

    bool isWithin(const sigrid::Position_f& point) const;

    float getRadius() const;

    sigrid::Position_f getCenterPosition() const;

    void show();

    void hide();

    void move(const sigrid::Offset_f& offset);

  private:

    bool m_isInitialized = false;
    void init();

    sigrid::Color getColor(const int& turnToMove) const;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool m_isVisible = false;
    sf::CircleShape m_shape;
};

}  // namespace sigrid