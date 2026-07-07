#pragma once

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <optional>

#include "List/Map.h"

namespace sigrid{

    class FontManager{

        public:
            FontManager();
            std::optional<sf::Font*> getFontPtr(const std::string& filename);

        private:

            list::Map<std::string, sf::Font> m_fonts;

    };
}