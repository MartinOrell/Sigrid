#include "ColorManager.h"

using namespace sigrid;

ColorManager::ColorManager(const std::vector<uint32_t>& colors){

    for(const auto& colorHex : colors){
        m_colors.push_back(sf::Color(colorHex));
    }
}

std::optional<sf::Color> ColorManager::getSolidColor(const int colorId) const{

    auto color_o = m_colors.at(colorId);
    if(color_o == std::nullopt){
        return std::nullopt;
    }
    const auto& color = color_o.value().get();

    return color;
}

std::optional<sf::Color> ColorManager::getTransparentColor(const int colorId) const{

    auto color_o = m_colors.at(colorId);
    if(color_o == std::nullopt){
        return std::nullopt;
    }
    sf::Color color = color_o.value().get();

    color.a = 0x80;
    return color;
}