#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace sigrid{

class GraphicCircle: public sf::Drawable{

  public:

    GraphicCircle();
    GraphicCircle(const GraphicCircle&);
    GraphicCircle& operator =(const GraphicCircle&);

    void setPosition(const sf::Vector2f& position);
    void setColor(const sf::Color& color);
    void setDiameter(const float& diameter);

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    sf::CircleShape m_shape;
};

}  // namespace sigrid