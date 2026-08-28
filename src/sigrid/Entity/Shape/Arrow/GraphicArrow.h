#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Offset/Offset_f.h"
#include "sigrid/utilities/Color/Color.h"

namespace sf{
    class Color;
}

namespace sigrid{

class GraphicArrow: public sf::Drawable{

  public:

    GraphicArrow() = default;
    GraphicArrow(const GraphicArrow&) = default;
    GraphicArrow(GraphicArrow&&) = default;
    GraphicArrow& operator=(const GraphicArrow&) = default;
    GraphicArrow& operator=(GraphicArrow&&) = default;

    void setFromPosition(const sigrid::Position_f& fromPosition);

    void setToPosition(const sigrid::Position_f& toPosition);

    void setPosition(const sigrid::Position_f& fromPosition, const sigrid::Position_f& toPosition);

    void setColor(const sigrid::Color& color);

    void setThickness(const float& thickness);

    void setHeadSize(const float& size);

    void setPosition(const sigrid::Position_f& position);

    void move(const sigrid::Offset_f& offset);

  private:

    struct IsSet{
        bool fromPosition = false;
        bool toPosition = false;
        bool thickness = false;
        bool headSize = false;
        bool isAllSet();
    };

    IsSet m_isSet;
    void updateShape();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    
    //Since Convex shape cannot draw concave shapes, multiple shapes are required
    sf::ConvexShape m_line;
    sf::CircleShape m_head;

    float m_thickness = 0.f;
    float m_headSize = 0.f;

    sigrid::Position_f m_toPosition = {0.f, 0.f};
};

}  // namespace sigrid