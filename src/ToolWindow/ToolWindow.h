#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Tool/Tool.h"
#include "ToolItem.h"
#include <SFML/Graphics/Font.hpp>
#include <memory>
#include "../Tool/ToolManager.h"

#include <SFML/Window/Event.hpp>

namespace sigrid{
    class ToolWindow: public sf::Drawable{
        public:
            ToolWindow(ToolManager* toolManagerPtr);

            void createGraphic(const sf::Vector2u& size);

            virtual void setPosition(sf::Vector2f);

            void setItemTexture(const unsigned int id, const sf::Texture* texturePtr, bool resetRect = false);

            bool isHidden() const;

            bool contains(sf::Vector2i point) const;

            Action clicked(const sigrid::Tool& tool, const sf::Vector2i& position);

            void setSetPieceTool(const Piece& piece);

            void setSelectTool(const sf::Mouse::Button button, const ToolSelection selection);

            void setAddArrowTool(const int colorId);

            void show();

            void hide();

            
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void redrawTexture();

            std::optional<int> getToolItemId(sf::Vector2i point);

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