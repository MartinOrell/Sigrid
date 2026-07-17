#pragma once

#include <string>
#include <optional>
#include <SFML/Graphics/Text.hpp>
#include "Action/Action.h"

namespace sf{
    class RectangleShape;
}

namespace sigrid{

class MenuItem: public sf::Drawable{

  public:

    MenuItem();
    MenuItem(const MenuItem& src);
    MenuItem& operator=(const MenuItem& rhs);

    void createGraphic(const int height);

    void setName(const std::string& name);
    void setFont(const sf::Font& font);
    void setPosition(const sf::Vector2f& position);
    void setAction(const sigrid_action::Action& action);
    void setText(const std::string& text);
    float getPositionLeft();
    float getPositionRight();
    float getPositionTop();
    bool isWithin(const sf::Vector2f& point, const float& maxYPos, const float& minYPos);
    sigrid_action::Action getAction();
    std::string getName();
    void addToggle(const std::string& text, const sigrid_action::Action&);
    void toggle();

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::string m_name = "";
    sf::RectangleShape m_shape;
    sigrid_action::Action m_action;

    std::optional<sf::Text> m_text_o;
    sf::Vector2f m_textOffset = {15.f,5.f};

    bool m_isToggled = false;
    std::string m_toggledName = "";
    sigrid_action::Action m_toggledAction;
};

}  // namespace sigrid