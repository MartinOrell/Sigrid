#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "sigrid/utilities/Texture/Texture.h"

namespace sigrid{

class GraphicPiece: public sf::Drawable{

  public:

    GraphicPiece() = default;
    GraphicPiece(const GraphicPiece&) = default;
    GraphicPiece(GraphicPiece&&) = default;
    GraphicPiece& operator=(const GraphicPiece&) = default;
    GraphicPiece& operator=(GraphicPiece&&) = default;

    void setSize(const sf::Vector2f& size);
    void setTexturePtr(const sigrid::Texture* const texturePtr);

    void setPosition(sf::Vector2f);
    bool contains(sf::Vector2i point) const;
    void resize(sf::Vector2f size);

    const sigrid::Texture getTexture() const;
    const sigrid::Texture* getTexturePtr() const;

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f m_size = {0.f,0.f};
    std::optional<sf::Sprite> m_sprite_o = std::nullopt;
    const sigrid::Texture* m_texturePtr;
};

}  // namespace sigrid