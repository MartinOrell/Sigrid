#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

class GraphicTile: public sf::Drawable{

  public:

    GraphicTile() = default;
    GraphicTile(const GraphicTile&) = default;
    GraphicTile(GraphicTile&&) = default;
    GraphicTile& operator=(const GraphicTile& rhs) = default;
    GraphicTile& operator=(GraphicTile&& rhs) = default;

    void setSize(const sf::Vector2f& size);

    void setPosition(const sf::Vector2f& topLeftPosition);

    void setTileColor(const sf::Color& color);

    void setHighlightColor(const sf::Color& color);

    void removeHighlight();

    sf::Vector2f getSize() const;

    sf::Vector2f getTopLeftPosition() const;

    sf::Vector2f getCentrePosition() const;

    float getRightPosition() const;

    float getTopPosition() const;

    sf::Color getColor() const;

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    sf::RectangleShape m_shape;
    bool m_isHighlightVisible = false;
    sf::RectangleShape m_highlight;
};

}  // namespace sigrid