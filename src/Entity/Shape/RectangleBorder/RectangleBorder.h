#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

class RectangleBorder: public sf::Drawable{

  public:

    RectangleBorder();

    void setThickness(const float& thickness);

    void setTopLeftPosition(const sf::Vector2f& topLeftPosition);

    void setEnclosedArea(const sf::Vector2f& enclosedArea);

    void setColor(const sf::Color& color);

    RectangleBorder& operator =(const RectangleBorder& rhs);

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

    sf::Vector2f m_topLeftPosition = {0.f,0.f};
    sf::Vector2f m_enclosedArea = {0.f,0.f};

    sf::RectangleShape m_left;
    sf::RectangleShape m_right;
    sf::RectangleShape m_top;
    sf::RectangleShape m_bottom;

};

}  // namespace sigrid