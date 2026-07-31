#pragma once

#include <optional>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/RenderTexture.hpp>

namespace sigrid{

class SigridRenderTexture: public sf::Drawable{

  public:

    SigridRenderTexture() = default;
    SigridRenderTexture(const SigridRenderTexture&) = default;
    SigridRenderTexture(SigridRenderTexture&&) = default;
    SigridRenderTexture& operator=(const SigridRenderTexture&) = default;
    SigridRenderTexture& operator=(SigridRenderTexture&&) = default;

    void setBackgroundColor(const sf::Color& color);
    bool setSize(const sf::Vector2f& size);
    void setPosition(const sf::Vector2f& position);
    void setScale(const float& scale);
    void show();
    void hide();

    const sf::Color& getBackgroundColor() const;
    const sf::Vector2f& getPosition() const;
    const float& getTopPosition() const;
    float getBottomPosition() const;
    const float& getScale() const;
    sf::Vector2f getTextureSize() const;
    sf::Vector2f getDisplaySize() const;
    sf::Image getImage() const;
    sf::Image getImage(const int maxWidth, const int maxHeight) const;

    bool isInitialized() const;
    bool isVisible() const;
    bool isHidden() const;
    bool contains(const sf::Vector2f& point) const;

    void clear();
    void draw(const sf::Drawable& drawable);
    void display();

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RenderTexture m_texture;
    std::optional<sf::Sprite> m_sprite_o = std::nullopt;
    sf::Color m_backgroundColor = sf::Color{255,255,255,0};
    sf::Vector2f m_position;
    float m_scale = 1.f;
    bool m_show = true;

};

}  // namespace sigrid