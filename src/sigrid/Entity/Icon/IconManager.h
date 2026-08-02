#pragma once

#include <optional>

#include <SFML/Graphics/Texture.hpp>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Map.h"

namespace sigrid{

class IconManager{

  public:

    IconManager() = default;
    IconManager(const IconManager&) = default;
    IconManager(IconManager&&) = default;
    IconManager& operator=(const IconManager&) = default;
    IconManager& operator=(IconManager&&) = default;

    std::optional<sf::Texture*> getTexturePtr(const sigrid::String& filename);
    
  private:

    sigrid_list::Map<sigrid::String, sf::Texture> m_textures;
};

}  // namespace sigrid