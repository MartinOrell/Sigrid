#include "sigrid/Color/ColorManager.h"

using namespace sigrid;

void ColorManager::setColors(const sigrid_list::Vector<ColorContainer>& colors){

    for(const auto& colorHex : colors){
        m_colors.push_back(sf::Color(colorHex.value));
    }
}

sigrid_list::Vector<ColorContainer> ColorManager::getContainer(){

    sigrid_list::Vector<ColorContainer> containers;
    for(const auto& color: m_colors){
        ColorContainer container;
        container.value = color.toInteger() / 0x100;
        containers.push_back(container);
    }

    return containers;
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