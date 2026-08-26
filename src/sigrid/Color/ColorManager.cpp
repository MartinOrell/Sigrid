#include "sigrid/Color/ColorManager.h"

void sigrid::ColorManager::setColors(const sigrid_list::Vector<ColorContainer>& colors){

    for(const auto& colorHex : colors){

        sigrid::Color color;
        color.setRGBA(colorHex.value);
        m_colors.push_back(color);
    }
}

sigrid_list::Vector<sigrid::ColorContainer> sigrid::ColorManager::getContainer(){

    sigrid_list::Vector<ColorContainer> containers;
    for(const auto& color: m_colors){
        ColorContainer container;
        container.value = color.getRGBInteger();
        containers.push_back(container);
    }

    return containers;
}

std::optional<sf::Color> sigrid::ColorManager::getSolidColor(const int colorId) const{

    auto color_o = m_colors.at(colorId);
    if(color_o == std::nullopt){
        return std::nullopt;
    }
    const auto& color = color_o.value().get();

    return color.getSolidSfColor();
}

std::optional<sf::Color> sigrid::ColorManager::getTransparentColor(const int colorId) const{

    auto color_o = m_colors.at(colorId);
    if(color_o == std::nullopt){
        return std::nullopt;
    }
    sigrid::Color color = color_o.value().get();

    color.a = 0x80;
    return color.getSfColor();
}