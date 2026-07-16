#include "Entity/Icon/IconManager.h"

#include <iostream>

using namespace sigrid;

std::optional<sf::Texture*> IconManager::getTexturePtr(const std::string& filename){

    auto m_texture_o = m_textures.at(filename);

    if(m_texture_o != std::nullopt){
        auto& texture = m_texture_o.value().get();
        return &texture;
    }

    sf::Texture newTexture;
    if(!newTexture.loadFromFile(filename)){
        std::cerr << "IconManager: failed to load from file: " << filename << std::endl;
        return std::nullopt;
    }

    auto inserted_texture_o = m_textures.insert(filename, newTexture);
    if(inserted_texture_o == std::nullopt){
        std::cerr << "IconManager: failed inserting texture from file " << filename << std::endl;
        return std::nullopt;
    }
    return &(inserted_texture_o.value().get());
}