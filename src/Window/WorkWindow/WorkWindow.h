#pragma once

#include <memory>
#include <vector>

#include "../../Layout/LayoutGrid.h"
#include "../../Board/Board.h"
#include "../../Action/Action.h"
#include <SFML/Window/Event.hpp>

#include "../../Entity/Shape/RectangleBorder/RectangleBorder.h"

namespace sf{
    class RenderTexture;
}

namespace sigrid{

    class BoardDataContainer;
    class Tool;

    class WorkWindow: public sf::Drawable{
        public:
            WorkWindow();

            void setBoardFilename(const std::string& filename);

            void setResetBoardFilename(const std::string& filename);

            void setDefaultBoardImageFilename(const std::string& filename);

            void setTileColorManagerPtr(ColorManager* const managerPtr);

            void setPieceManagerPtr(PieceManager* const managerPtr);

            void setArrowColorManagerPtr(ColorManager* const managerPtr);

            void setFontManagerPtr(FontManager* const managerPtr);

            void init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData);

            void createGraphic(const sf::Vector2u& size);

            void loadFen(const std::string& fen);

            std::string getName() const;

            std::string getSaveFilename() const;

            std::string getFen() const;
            
            void setPosition(const sf::Vector2f& position);

            unsigned int getNumColumns() const;

            bool contains(const sf::Vector2f& point) const;

            bool isCoordinatesOutside() const;

            void mousePress(const sf::Vector2f& position);
            Action clicked(const sigrid::Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& releasePosition);
            void dragMouse(const Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& currentPosition);

            void reset();

            void clear();

            void print();

            void newBoard();

            void openLeftBoard();
            void openRightBoard();

            void saveBoard();
            void savePdf();

            void flipBoard();

            void addLeftInsideLabels();
            void addBottomInsideLabels();
            void addLeftOutsideLabels();
            void addRightOutsideLabels();
            void addTopOutsideLabels();
            void addBottomOutsideLabels();
            
            void removeLeftInsideLabels();
            void removeBottomInsideLabels();
            void removeLeftOutsideLabels();
            void removeRightOutsideLabels();
            void removeTopOutsideLabels();
            void removeBottomOutsideLabels();

            void setCoordinateSize(const float& size);

            void addTileColumnRight();

            void addTileColumnLeft();

            void removeTileColumnRight();

            void removeTileColumnLeft();

            void addTileRowUp();

            void addTileRowDown();

            void removeTileRowUp();

            void removeTileRowDown();

            void addBoardBorder();

            void removeBoardBorder();

            void addTurnToken();

            void removeTurnToken();

            void useAddEntityTool(const Coord& coord, const LogicEntity& newEntity);
            void useAddEntityAtSelectionTool(const LogicEntity& newEntity);

        private:

            sigrid::Board& activeBoard();
            const sigrid::Board& activeBoard() const;

            int& activeId();
            const int& activeId() const;

            std::string getUniqueName(const std::string& name);

            void useAddTileHighlightTool(const Coord& coord, const int& colorId);
            void useAddArrowTool(const Coord& fromCoord, const Coord& toCoord, const int& colorId);

            void updateSelectionHighlight();

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            typedef unsigned int LayoutItem;

            std::unique_ptr<sf::RenderTexture> m_texture;
            sf::Vector2f m_position;
            LayoutGrid m_layout;
            std::vector<sigrid::Board> m_boards;
            unsigned int m_maxBoardColumns = 2;
            unsigned int m_maxBoardRows = 2;
            std::vector<int> m_displayBoardIds;
            int m_activeBoardIndex = 0;

            RectangleBorder m_boardSelectHighlight;

            sf::Color m_backgroundColor;

            std::string m_resetBoardFilename = "";
            std::string m_defaultBoardImageFilename = "";
    };
}