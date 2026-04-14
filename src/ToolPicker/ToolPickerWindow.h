#pragma once

#include <memory>
#include <map>

#include <SFML/System/Vector2.hpp>
#include "../Action/Action.h"
#include "../Coord/CoordBlock.h"
#include "../Color/ColorManager.h"
namespace sf{
    class RenderTexture;
}

namespace sigrid{

    class ToolPickerContainer;
    class PieceManager;
    class ToolManager;

    class GraphicToolPicker;
    class Tool;

    class ToolPickerWindow: public sf::Drawable{
        public:

            ToolPickerWindow(const ToolPickerContainer& data, ColorManager* const tileColorManagerPtr, PieceManager* const pieceManagerPtr, ToolManager* const toolManagerPtr);
            
            void createGraphic(const sf::Vector2u& size);

            void addSelectTool();

            void addArrowTool(const int colorId);

            void addCircleTool(const int colorId);

            void addPieceTool(const std::string& notation);

            virtual void setPosition(const sf::Vector2f& position);

            bool isHidden() const;

            sf::Vector2u getSize() const;

            unsigned int getNumColumns() const;

            unsigned int getNumRows() const;

            bool contains(const sf::Vector2f& point) const;

            Action clicked(const sigrid::Tool& tool, const sf::Vector2f& position);

            void setPieceColorTools(const std::string& pieceNotation);

            void setPieceTools(const int colorId);

            void setArrowColors();

            void setCircleColors();

            void setAddArrowTool(const int colorId);

            void setAddCircleTool(const int colorId);

            void hideColorTools();

            void showColorTools();

            void hide();

            void show();

        private:

            void redrawTexture();

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            enum ColorDisplay{
                None,
                Piece,
                Arrow,
                Circle
            };

            struct ToolStruct{
                sf::Texture* texturePtr;
                Action action;
            };

            int m_columns;
            int m_rows;

            std::vector<ToolStruct> m_miscTools;

            ColorDisplay m_colorDisplay;

            std::unique_ptr<sf::RenderTexture> m_texture;
            sf::Vector2f m_position;
            std::unique_ptr<sigrid::GraphicToolPicker> m_boardPtr;

            PieceManager* m_pieceManagerPtr;
            ToolManager* m_toolManagerPtr;

            std::map<Coord, Action> m_clickActions;

            std::vector<int> m_displayedPieceColorIds;
            int m_arrowColorId;
            int m_circleColorId;
            std::string m_pieceNotation;

            std::vector<std::string> m_pieceNotations;

            bool m_show;

            bool m_showColors;

            sf::Color m_backgroundColor;

            std::vector<int> m_colorIds;

            CoordBlock m_miscBlock;
            CoordBlock m_colorBlock;
            std::vector<CoordBlock> m_pieceBlocks;

            int m_defaultArrowColorId;
            int m_defaultCircleColorId;
    };
}