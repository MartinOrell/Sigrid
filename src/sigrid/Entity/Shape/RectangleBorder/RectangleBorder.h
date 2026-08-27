#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "sigrid/utilities/Size/Size_f.h"
#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Color/Color.h"

#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorderContainer.h"

namespace sigrid{

class RectangleBorder: public sf::Drawable{

  public:

    RectangleBorder() = default;
    RectangleBorder(const RectangleBorder&) = default;
    RectangleBorder(RectangleBorder&&) = default;
    RectangleBorder& operator=(const RectangleBorder&) = default;
    RectangleBorder& operator=(RectangleBorder&&) = default;

    RectangleBorderContainer getContainer() const;

    void setThickness(const float& thickness);

    void setTopLeftPosition(const sigrid::Position_f& topLeftPosition);

    void setEnclosedArea(const sigrid::Size_f& enclosedArea);

    void setColor(const sigrid::Color& color);

    bool isVisible() const;
    bool isHidden() const;

    float getThickness() const;

    void show();

    void hide();

    void addWidth(const float& addedWidth);
    void addHeight(const float& addedHeight);

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    bool m_isVisible = true;
    float m_thickness = 0.f;

    sigrid::Position_f m_topLeftPosition = {0.f,0.f};
    sigrid::Size_f m_enclosedArea = {0.f,0.f};

    sf::RectangleShape m_left;
    sf::RectangleShape m_right;
    sf::RectangleShape m_top;
    sf::RectangleShape m_bottom;

};

}  // namespace sigrid