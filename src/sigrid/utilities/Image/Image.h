#pragma once

#include <SFML/Graphics/Image.hpp>

#include "sigrid/utilities/String/String.h"

namespace sigrid{

class Image{

  public:
    Image() = default;
    Image(const Image&) = default;
    Image(Image&&) = default;
    Image& operator=(const Image&) = default;
    Image& operator=(Image&&) = default;

    void set(sf::Image&&);

    int getWidth() const;
    int getHeight() const;
    sigrid::String getAsciiHexStream() const;

    bool saveToFile(const sigrid::String& filename) const;

  private:

    sf::Image m_image;
};

}  // namespace sigrid