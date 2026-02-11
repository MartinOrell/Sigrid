#pragma once

#include <vector>
#include <SFML/Graphics/Color.hpp>
#include <string>

namespace sigrid{
    class ColorManager{

        public:
            ColorManager(const std::vector<uint32_t>& colors);

            sf::Color getSolidColor(const int colorId) const;
            sf::Color getTransparentColor(const int colorId) const;

        private:
            std::vector<sf::Color> m_colors;

    };
}