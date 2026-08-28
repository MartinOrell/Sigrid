#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Offset/Offset_f.h"
#include "sigrid/utilities/Size/Size_f.h"
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

    void setPosition(const sigrid::Position_f& position);
    bool contains(const sf::Vector2i& point) const;
    void resize(const sigrid::Size_f& size);

    const sigrid::Texture getTexture() const;
    const sigrid::Texture* getTexturePtr() const;

    void move(const sigrid::Offset_f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::Vector2f m_size = {0.f,0.f};
    std::optional<sf::Sprite> m_sprite_o = std::nullopt;
    const sigrid::Texture* m_texturePtr;
};

}  // namespace sigrid