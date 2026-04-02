#pragma once

#include <map>
#include <SFML/Graphics/Font.hpp>
#include <string>
#include <optional>

namespace sigrid{

    class FontManager{

        public:
            FontManager();
            std::optional<sf::Font*> getFontPtr(const std::string& filename);

        private:

            std::map<std::string, sf::Font> m_fonts;

    };
}