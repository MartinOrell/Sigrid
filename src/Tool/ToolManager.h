#pragma once

#include <map>
#include "Tool.h"
#include <SFML/Graphics/Texture.hpp>
#include <memory>
#include "../Arrow/GraphicArrow.h"
#include "../Color/ColorManager.h"

namespace sigrid{

    class ToolManager{

        public:
            ToolManager(ColorManager* _colorManagerPtr);
            std::optional<sf::Texture*> getTexturePtr(const ToolSelection& selection);
            std::optional<sf::Texture*> getArrowTexturePtr(const int colorId);
        private:
            std::map<ToolSelection, sf::Texture> m_toolTextures;
            std::map<int, sf::Texture> m_arrowTextures;

            std::unique_ptr<GraphicArrow> m_graphicArrowPtr;

            ColorManager* m_colorManagerPtr;
    };

}