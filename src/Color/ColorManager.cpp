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

sf::Color ColorManager::getSolidColor(const int colorId) const{
    //Change to optional and check colorId
    return m_colors.at(colorId);
}

sf::Color ColorManager::getTransparentColor(const int colorId) const{
    //Change to optional and check colorId
    sf::Color color = m_colors.at(colorId);
    color.a = 0x80;
    return color;
}