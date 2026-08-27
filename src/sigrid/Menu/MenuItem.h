#pragma once

#include <string>
#include <optional>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/Menu/MenuItemContainer.h"
#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/GraphicText/GraphicText.h"
#include "sigrid/Action/Action.h"

namespace sf{
    class RectangleShape;
}

namespace sigrid{

class MenuItem: public sf::Drawable{

  public:

    MenuItem() = default;
    MenuItem(const MenuItem&) = default;
    MenuItem(MenuItem&&) = default;
    MenuItem& operator=(const MenuItem&) = default;
    MenuItem& operator=(MenuItem&&) = default;

    MenuItemContainer getContainer() const;

    void createGraphic(const int height);

    void setName(const sigrid::String& name);
    void setFont(const sf::Font& font);
    void setPosition(const sf::Vector2f& position);
    void setAction(const sigrid_action::Action& action);
    void setText(const sigrid::String& text);
    float getPositionLeft() const;
    float getPositionRight() const;
    float getPositionTop() const;
    bool isWithin(const sigrid::Position_f& point, const float& maxYPos, const float& minYPos) const;
    sigrid_action::Action getAction() const;
    sigrid::String getName() const;
    void addToggle(const sigrid::String& text, const sigrid_action::Action&);
    void toggle();

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sigrid::String m_name = "";
    sf::RectangleShape m_shape;
    sigrid_action::Action m_action;

    sigrid::GraphicText m_text;
    sf::Vector2f m_textOffset = {15.f,5.f};

    bool m_isToggled = false;
    sigrid::String m_toggledName;
    sigrid_action::Action m_toggledAction;
};

}  // namespace sigrid