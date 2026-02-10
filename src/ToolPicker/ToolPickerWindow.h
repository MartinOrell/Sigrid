#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>

#include "GraphicToolPicker.h"

#include "../Tool/Tool.h"

#include "../Action/Action.h"

#include "../Tool/ToolManager.h"

#include "../MainWindow/MainWindowConfigContainer.h"

namespace sigrid{
    class ToolPickerWindow: public sf::Drawable{
        public:

            ToolPickerWindow(const MainWindowConfigContainer& wConfig, PieceManager* pieceManagerPtr, ToolManager* toolManagerPtr, const std::vector<sf::Color> squareColors);
            
            void createGraphic(const sf::Vector2u& size);

            void addSelectTool();

            void addArrowTool();

            void addPieceTool(std::string notation);

            void addPieceColorTools(const int numColors);

            virtual void setPosition(sf::Vector2f);

            bool isHidden() const;

            sf::Vector2u getSize() const;

            unsigned int getNumColumns() const;

            unsigned int getNumRows() const;

            bool contains(sf::Vector2i point) const;

            Action clicked(const sigrid::Tool& tool, const sf::Vector2i& position);

            void setPieceColorTools(const std::string& pieceNotation);

            void setPieceTools(const int colorId);

            void setArrowColors();

            void setAddArrowTool(const int colorId);

            void hideColorTools();

            void showColorTools();

            void hide();

            void show();

        private:

            void redrawTexture();

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            enum ColorDisplay{
                Piece,
                Arrow
            };

            struct ToolStruct{
                sf::Texture* texturePtr;
                Action action;
            };

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
            std::string m_pieceNotation;

            std::vector<std::string> m_pieceNotations;

            bool m_show;

            bool m_showColors;
            int m_colorColumns;
            //Coord m_firstColorPos;

            int m_numPieceColors;
            int m_numArrowColors;

            //Coord m_nextToolCoord;

            sf::Color m_backgroundColor;
    };
}