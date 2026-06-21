#pragma once

#include <memory>
#include <vector>
#include <optional>

#include <SFML/Graphics/Drawable.hpp>

#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

#include "../../Action/Action.h"
#include "../../Board/Board.h"

#include "../../SigridRenderTexture/SigridRenderTexture.h"

namespace sigrid{

    class ToolWindow: public sf::Drawable{
        public:
            ToolWindow();

            void setTileColorManagerPtr(ColorManager* const managerPtr);

            void setIconManagerPtr(IconManager* const managerPtr);

            void setPieceManagerPtr(PieceManager* const managerPtr);

            void setArrowColorManagerPtr(ColorManager* const managerPtr);

            void init();

            void createGraphic(const sf::Vector2f& size);

            virtual void setPosition(const sf::Vector2f& position);

            bool isVisible() const;
            bool isHidden() const;

            bool contains(const sf::Vector2f& point) const;

            void setSetPieceTool(const LogicPiece& logicPiece);

            void setSelectTool(const sf::Mouse::Button button, const ToolSelection selection);

            void setAddArrowTool(const int colorId);

            void setAddCircleTool(const int colorId);

            void show();

            void hide();

            
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void redrawTexture();

            bool m_show;

            SigridRenderTexture m_texture;

            Board m_board;
    };
}