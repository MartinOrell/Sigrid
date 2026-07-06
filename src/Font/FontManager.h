#pragma once

#include <SFML/Graphics/Font.hpp>
#include <string>
#include <optional>

#include "List/SigridMap.h"

namespace sigrid{

    class FontManager{

        public:
            FontManager();
            std::optional<sf::Font*> getFontPtr(const std::string& filename);

        private:

            SigridMap<std::string, sf::Font> m_fonts;

    };
}