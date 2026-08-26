#pragma once

#include <optional>

#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "sigrid/utilities/String/String.h"

namespace sigrid{

class GraphicText: public sf::Drawable{

  public:

    GraphicText() = default;
    GraphicText(const GraphicText&) = default;
    GraphicText(GraphicText&&) = default;
    GraphicText& operator=(const GraphicText&) = default;
    GraphicText& operator=(GraphicText&&) = default;

    void setFont(const sf::Font& font);
    void setString(const sigrid::String& string);
    bool setCharacterSize(const int& size);

    void setOrigin(const sf::Vector2f& origin); 
    void setPosition(const sf::Vector2f& position);
    void setFillColor(const sf::Color& color);
    void setOutlineColor(const sf::Color& color);
    void setOutlineThickness(const float& thickness);

    float getLocalWidth() const;

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    std::optional<sf::Text> m_text_o = std::nullopt;
};

}  // namespace sigrid

