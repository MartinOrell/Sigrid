#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Size/Size_f.h"
#include "sigrid/utilities/Texture/Texture.h"

namespace sigrid{

class Icon: public sf::Drawable{

  public:

    Icon() = default;
    Icon(const Icon&) = default;
    Icon(Icon&&) = default;
    Icon& operator=(const Icon&) = default;
    Icon& operator=(Icon&&) = default;
    
    void setSize(const sigrid::Size_f& size);

    void setPosition(const sigrid::Position_f& position);

    void setTexture(const sigrid::Texture* texturePtr);

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    sf::RectangleShape m_shape;
};

}  // namespace sigrid