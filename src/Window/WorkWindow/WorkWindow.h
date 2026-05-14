#pragma once

#include <memory>
#include <vector>

#include "../../Board/Board.h"
#include "../../Action/Action.h"
#include <SFML/Window/Event.hpp>

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

            Action clicked(const sigrid::Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& releasePosition);
            void dragMouse(const Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& currentPosition);

            void reset();

            void clear();

            void print();

            void newBoard();

            void openLeftBoard();
            void openRightBoard();

            void saveBoard();

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

            std::string getUniqueName(const std::string& name);

            void useAddTileHighlightTool(const Coord& coord, const int& colorId);
            void useAddArrowTool(const Coord& fromCoord, const Coord& toCoord, const int& colorId);

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<sf::RenderTexture> m_texture;
            sf::Vector2f m_position;
            std::vector<sigrid::Board> m_boards;
            int m_activeBoardId;

            sf::Color m_backgroundColor;

            std::string m_defaultBoardImageFilename = "";
    };
}