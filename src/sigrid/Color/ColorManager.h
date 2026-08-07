#pragma once

#include <SFML/Graphics/Color.hpp>
#include <optional>

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Color/ColorContainer.h"

namespace sigrid{

class ColorManager{

  public:

    ColorManager() = default;
    ColorManager(const ColorManager&) = default;
    ColorManager(ColorManager&&) = default;
    ColorManager& operator=(const ColorManager&) = default;
    ColorManager& operator=(ColorManager&&) = default;

    void setColors(const sigrid_list::Vector<ColorContainer>& colors);
    sigrid_list::Vector<ColorContainer> getContainer();

    std::optional<sf::Color> getSolidColor(const int colorId) const;
    std::optional<sf::Color> getTransparentColor(const int colorId) const;

  private:

    sigrid_list::Vector<sf::Color> m_colors;

};

}  // namespace sigrid