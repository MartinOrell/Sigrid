#pragma once

#include <SFML/Graphics/Texture.hpp>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/Image/Image.h"

namespace sigrid{

class Texture{

  public:
    Texture() = default;
    Texture(const Texture&) = default;
    Texture(Texture&&) = default;
    Texture& operator=(const Texture&) = default;
    Texture& operator=(Texture&&) = default;

    bool loadFromFile(const sigrid::String& filename);
    bool loadFromImage(const sigrid::Image& image);

    const sf::Texture& getSfTexture() const;

  private:

    sf::Texture m_texture;
};

}  // namespace sigrid