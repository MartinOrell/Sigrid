#pragma once

#include <optional>
#include <map>

#include <string>
#include <SFML/Graphics/Texture.hpp>

namespace sigrid{

    class IconManager{

        public:
            IconManager();
            std::optional<sf::Texture*> getTexturePtr(const std::string& filename);
            
        private:
            std::map<std::string, sf::Texture> m_textures;
    };

}