#pragma once

#include <SFML/Graphics/Font.hpp>
#include <optional>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Map.h"

namespace sigrid{

class FontManager{

  public:

    FontManager() = default;
    FontManager(const FontManager&) = default;
    FontManager(FontManager&&) = default;
    FontManager& operator=(const FontManager&) = default;
    FontManager& operator=(FontManager&&) = default;
    
    std::optional<sf::Font*> getFontPtr(const sigrid::String& filename);

  private:

    sigrid_list::Map<sigrid::String, sf::Font> m_fonts;

};

}  // namespace sigrid