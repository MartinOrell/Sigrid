#pragma once

#include <optional>

#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "List/SigridMap.h"

namespace sigrid{

    class IconManager{

        public:
            IconManager();
            std::optional<sf::Texture*> getTexturePtr(const std::string& filename);
            
        private:
            list::SigridMap<std::string, sf::Texture> m_textures;
    };

}