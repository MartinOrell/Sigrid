#include "Font/FontManager.h"

#include <iostream>

using namespace sigrid;

std::optional<sf::Font*> FontManager::getFontPtr(const std::string& filename){

    auto font_o = m_fonts.at(filename);
    if(font_o != std::nullopt){
        return &(font_o.value().get());
    }

    sf::Font newFont;
    if(!newFont.openFromFile(filename)){
        std::cerr << "FontManager: Failed to load font: "
            << filename << std::endl;
        return std::nullopt;
    }

    auto insertedFont_o = m_fonts.insert(filename, newFont);
    if(insertedFont_o == std::nullopt){
        std::cerr << "FontManager: failed inserting font: "
            << filename << std::endl;
        return std::nullopt;
    }
    return &(insertedFont_o.value().get());
}