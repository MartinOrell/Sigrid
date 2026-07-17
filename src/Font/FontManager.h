#pragma once

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <optional>

#include "List/Map.h"

namespace sigrid{

class FontManager{

  public:

    FontManager() = default;
    FontManager(const FontManager&) = default;
    FontManager(FontManager&&) = default;
    FontManager& operator=(const FontManager&) = default;
    FontManager& operator=(FontManager&&) = default;
    
    std::optional<sf::Font*> getFontPtr(const std::string& filename);

  private:

    sigrid_list::Map<std::string, sf::Font> m_fonts;

};

}  // namespace sigrid