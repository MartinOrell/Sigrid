#pragma once

#include <memory>
#include <vector>
#include <optional>

#include <SFML/Graphics/Drawable.hpp>

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Action/Action.h"

namespace sf{
    class RenderTexture;
}

namespace sigrid{

    class Tool;
    class ToolItem;
    class ToolManager;

    class ToolWindow: public sf::Drawable{
        public:
            ToolWindow();

            void setToolManagerPtr(ToolManager* const managerPtr);

            void init();

            void createGraphic(const sf::Vector2u& size);

            virtual void setPosition(const sf::Vector2f& position);

            void setItemTexture(const unsigned int id, const sf::Texture* const texturePtr, bool resetRect = false);

            bool isHidden() const;

            bool contains(const sf::Vector2f& point) const;

            Action clicked(const sigrid::Tool& tool, const sf::Vector2f& position);

            void setSetPieceTool(const GraphicPiece& graphicPiece);

            void setSelectTool(const sf::Mouse::Button button, const ToolSelection selection);

            void setAddArrowTool(const int colorId);

            void setAddCircleTool(const int colorId);

            void show();

            void hide();

            
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void redrawTexture();

            std::optional<int> getToolItemId(const sf::Vector2f& point);

            bool m_show;

            std::unique_ptr<sf::RenderTexture> m_texture;
            sf::Vector2f m_position;

            std::vector<std::unique_ptr<ToolItem>> m_items;
            float m_itemOffsetX;

            ToolManager* m_toolManagerPtr;

            sf::Font m_font;

            sf::Color m_backgroundColor;
    };
}