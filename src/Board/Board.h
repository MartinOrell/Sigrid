#pragma once

#include <memory>
#include <optional>
#include <string>

#include "GraphicBoard.h"
#include "LogicBoard.h"
#include "../Entity/Piece/PieceManager.h"

namespace sigrid{

    class BoardDataContainer;
    class LogicTile;
    class IconManager;

    class Board: public sf::Drawable{
        public:            

            Board();
            Board(const Board& src);

            void setPieceManagerPtr(PieceManager* const managerPtr);
            void setTileColorManagerPtr(ColorManager* const managerPtr);
            void setArrowColorManagerPtr(ColorManager* const managerPtr);
            void setFontManagerPtr(FontManager* const managerPtr);
            void setIconManagerPtr(IconManager* const managerPtr);
            void setLeftToRight();
            void setRightToLeft();
            void setTopToBottom();
            void setBottomToTop();

            void init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData);

            Board& operator=(const Board& rhs);

            void setPosition(const sf::Vector2f& position);

            void setPositionX(const float x);

            void setScale(const float scale);

            void setFilename(const std::string& filename);

            void setImageFilename(const std::string& filename);

            unsigned int getNumColumns() const;

            unsigned int getImageWidth() const;

            unsigned int getImageHeight() const;

            float getDisplayWidth() const;

            float getDisplayHeight() const;

            std::string getName() const;

            std::string getFilename() const;

            std::string getImageFilename() const;

            bool contains(const sf::Vector2f& point) const;

            bool isEmptyTile(const Coord& coord) const;

            bool isCoordinatesOutside() const;

            bool isWithinTurnToken(const sf::Vector2f& point) const;

            bool isImageFilenameSet() const;

            std::optional<Coord> getTileCoord(const sf::Vector2f& point);

            std::optional<LogicTile> getTile(const Coord& coord);

            std::optional<LogicEntity> getLogicEntity(const Coord& coord);

            std::optional<LogicArrow> getLogicArrow(const CoordPair& coordPair);

            std::string getFen() const;

            void select(const Coord& coord);

            void deselect();

            void addEntity(const Coord& coord, const LogicEntity& newEntity);
            void removeEntity(const Coord& coord);

            void addEntityAtSelection(const LogicEntity& newEntity);
            void dragAndDrop(const Coord& fromCoord, const Coord& toCoord);

            void addArrow(const Coord& fromCoord, const Coord& toCoord, const LogicArrow& newArrow);
            void removeArrow(const Coord& fromCoord, const Coord& toCoord);

            void addTileHighlight(const Coord& coord, const int& colorId);
            void removeTileHighlight(const Coord& coord);

            void updateDragArrow(const Coord& fromCoord, const Coord& toCoord, const int& colorId);
            void removeDragArrow();

            void loadFen(const std::string& fen);

            void save();

            void clearEntities();
            void clearArrows();
            void print();

            void flipBoard();

            void addLeftInsideLabels();
            void addBottomInsideLabels();
            void addLeftOutsideLabels();
            void addTopOutsideLabels();
            void addBottomOutsideLabels();
            void removeLeftInsideLabels();
            void removeBottomInsideLabels();
            void removeLeftOutsideLabels();
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

            void addBorder();

            void removeBorder();

            void addTurnToken();

            void removeTurnToken();

            void toggleTurnToken();
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            LogicBoard m_logicBoard;

            GraphicBoard m_graphicBoard;

            std::unique_ptr<Coord> m_selection;

            std::string m_filename;
            std::string m_imageFilename;
    };
}