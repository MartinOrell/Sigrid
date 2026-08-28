#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "sigrid/utilities/Size/Size_f.h"
#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Color/Color.h"

namespace sigrid{

class GraphicTile: public sf::Drawable{

  public:

    GraphicTile() = default;
    GraphicTile(const GraphicTile&) = default;
    GraphicTile(GraphicTile&&) = default;
    GraphicTile& operator=(const GraphicTile& rhs) = default;
    GraphicTile& operator=(GraphicTile&& rhs) = default;

    void setSize(const sigrid::Size_f& size);

    void setPosition(const sigrid::Position_f& topLeftPosition);

    void setTileColor(const sigrid::Color& color);

    void setHighlightColor(const sigrid::Color& color);

    void removeHighlight();

    sigrid::Size_f getSize() const;

    sigrid::Position_f getTopLeftPosition() const;

    sigrid::Position_f getCentrePosition() const;

    float getRightPosition() const;

    float getTopPosition() const;

    sigrid::Color getColor() const;

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    sf::RectangleShape m_shape;
    bool m_isHighlightVisible = false;
    sf::RectangleShape m_highlight;
};

}  // namespace sigrid