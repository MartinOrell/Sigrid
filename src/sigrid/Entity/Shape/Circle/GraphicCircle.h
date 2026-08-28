#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Color/Color.h"

namespace sigrid{

class GraphicCircle: public sf::Drawable{

  public:

    GraphicCircle() = default;
    GraphicCircle(const GraphicCircle&) = default;
    GraphicCircle(GraphicCircle&&) = default;
    GraphicCircle& operator =(const GraphicCircle&) = default;
    GraphicCircle& operator =(GraphicCircle&&) = default;

    void setPosition(const sigrid::Position_f& position);
    void setColor(const sigrid::Color& color);
    void setDiameter(const float& diameter);

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    sf::CircleShape m_shape;
};

}  // namespace sigrid