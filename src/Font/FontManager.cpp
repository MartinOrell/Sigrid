#include "FontManager.h"

#include <iostream>

using namespace sigrid;

FontManager::FontManager(){};

std::optional<sf::Font*> FontManager::getFontPtr(const std::string& filename){
    auto it = m_fonts.find(filename);
    if(it == m_fonts.end()){
        sf::Font newFont;
        if(!newFont.openFromFile(filename)){
            std::cerr << "FontManager: Failed to load font: "
                << filename << std::endl;
            return std::nullopt;
        }
        m_fonts.insert({filename,newFont});
        return &(m_fonts.at(filename));
    }
    return &(m_fonts.at(filename));
}