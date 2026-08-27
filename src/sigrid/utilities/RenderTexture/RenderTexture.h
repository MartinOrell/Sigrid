#pragma once

#include <optional>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Image/Image.h"
#include "sigrid/utilities/Color/Color.h"

namespace sigrid{

class RenderTexture: public sf::Drawable{

  public:

    RenderTexture() = default;
    RenderTexture(const RenderTexture&) = default;
    RenderTexture(RenderTexture&&) = default;
    RenderTexture& operator=(const RenderTexture&) = default;
    RenderTexture& operator=(RenderTexture&&) = default;

    void setBackgroundColor(const sigrid::Color& color);
    bool setSize(const sf::Vector2f& size);
    void setPosition(const sigrid::Position_f& position);
    void setScale(const float& scale);
    void show();
    void hide();

    const sigrid::Color& getBackgroundColor() const;
    const sigrid::Position_f& getPosition() const;
    const float& getTopPosition() const;
    float getBottomPosition() const;
    const float& getScale() const;
    sf::Vector2f getTextureSize() const;
    sf::Vector2f getDisplaySize() const;
    sigrid::Image getImage() const;
    sigrid::Image getImage(const int maxWidth, const int maxHeight) const;

    bool isInitialized() const;
    bool isVisible() const;
    bool isHidden() const;
    bool contains(const sigrid::Position_f& point) const;

    void clear();
    void draw(const sf::Drawable& drawable);
    void display();

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RenderTexture m_texture;
    std::optional<sf::Sprite> m_sprite_o = std::nullopt;
    sigrid::Color m_backgroundColor;
    sigrid::Position_f m_position;
    float m_scale = 1.f;
    bool m_show = true;

};

}  // namespace sigrid