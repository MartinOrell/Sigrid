#include "IconManager.h"

#include <iostream>

using namespace sigrid;

IconManager::IconManager(){}

std::optional<sf::Texture*> IconManager::getTexturePtr(const std::string& filename){

    auto it = m_textures.find(filename);

    if(it != m_textures.end()){
        return &(it->second);
    }

    sf::Texture newTexture;
    if(newTexture.loadFromFile(filename)){
        m_textures.insert({filename, newTexture});
        return &(m_textures.at(filename));
    }

    std::cerr << "IconManager failed to load from file: " << filename << std::endl;
    return std::nullopt;
}