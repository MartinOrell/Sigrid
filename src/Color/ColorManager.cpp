#include "ColorManager.h"

#include <iostream>
#include <fstream>
#include <cassert>

using namespace sigrid;

ColorManager::ColorManager(const std::vector<uint32_t>& colors){
    for(const auto& colorHex : colors){
        m_colors.push_back(sf::Color(colorHex));
    }
}

std::optional<sf::Color> ColorManager::getSolidColor(const int colorId) const{
    if(colorId < 0 || colorId >= m_colors.size()){
        return std::nullopt;
    }
    return m_colors.at(colorId);
}

std::optional<sf::Color> ColorManager::getTransparentColor(const int colorId) const{
    if(colorId < 0 || colorId >= m_colors.size()){
        return std::nullopt;
    }
    sf::Color color = m_colors.at(colorId);
    color.a = 0x80;
    return color;
}