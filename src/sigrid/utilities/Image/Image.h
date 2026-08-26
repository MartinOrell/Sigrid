#pragma once

#include <SFML/Graphics/Image.hpp>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/Color/Color.h"

namespace sigrid{

class Image{

  public:
    Image() = default;
    Image(const Image&) = default;
    Image(Image&&) = default;
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&) = default;

    void set(sf::Image&&);

    sf::Image getSfImage() const;

    int getWidth() const;
    int getHeight() const;
    sigrid::String getAsciiHexStream() const;

    bool loadFromFile(const sigrid::String& filename);
    bool saveToFile(const sigrid::String& filename) const;

    void modifyColor(const sigrid::Color& lightModifier, const sigrid::Color& darkModifier);

  private:

    sf::Image m_image;
};

}  // namespace sigrid