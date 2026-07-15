#pragma once

#include <SFML/Graphics/Color.hpp>
#include <optional>

#include "List/Vector.h"

namespace sigrid{
    class ColorManager{

        public:
            ColorManager(const std::vector<uint32_t>& colors);

            std::optional<sf::Color> getSolidColor(const int colorId) const;
            std::optional<sf::Color> getTransparentColor(const int colorId) const;

        private:
            sigrid_list::Vector<sf::Color> m_colors;

    };
}