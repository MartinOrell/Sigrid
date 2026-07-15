#pragma once

#include <optional>

#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "List/Map.h"

namespace sigrid{

    class IconManager{

        public:
            IconManager();
            std::optional<sf::Texture*> getTexturePtr(const std::string& filename);
            
        private:
            sigrid_list::Map<std::string, sf::Texture> m_textures;
    };

}