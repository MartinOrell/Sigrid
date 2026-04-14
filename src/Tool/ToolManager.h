#pragma once

#include <memory>
#include <map>

#include <SFML/Graphics/Texture.hpp>

namespace sigrid{

    class ColorManager;
    enum ToolSelection;
    class GraphicArrow;
    class GraphicCircle;

    class ToolManager{

        public:
            ToolManager(ColorManager* const _colorManagerPtr);
            std::optional<sf::Texture*> getTexturePtr(const ToolSelection& selection);
            std::optional<sf::Texture*> getArrowTexturePtr(const int colorId);
            std::optional<sf::Texture*> getCircleTexturePtr(const int colorId);
        private:
            std::map<ToolSelection, sf::Texture> m_toolTextures;
            std::map<int, sf::Texture> m_arrowTextures;
            std::map<int, sf::Texture> m_circleTextures;

            std::unique_ptr<GraphicArrow> m_graphicArrowPtr;
            std::unique_ptr<GraphicCircle> m_graphicCirclePtr;

            ColorManager* m_colorManagerPtr;
    };

}