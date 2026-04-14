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

    class Board: public sf::Drawable{
        public:            

            Board();

            void init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData, ColorManager* const tileColorManagerPtr, PieceManager* const pieceManagerPtr, ColorManager* const arrowColorManagerPtr, FontManager* const fontManagerPtr);

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
            std::optional<GraphicEntity> getGraphicEntity(const Coord& coord);

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

            void addCoordinates();

            void removeCoordinates();

            void moveCoordinatesOutside();

            void moveCoordinatesInside();

            void setCoordinateSize(const float& size);

            void addSquareColumnRight();

            void addSquareColumnLeft();

            void removeSquareColumnRight();

            void removeSquareColumnLeft();

            void addSquareRowUp();

            void addSquareRowDown();

            void removeSquareRowUp();

            void removeSquareRowDown();

            void addBorder();

            void removeBorder();

            void addTurnToken();

            void removeTurnToken();

            void toggleTurnToken();
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<LogicBoard> m_logicBoard;

            std::unique_ptr<GraphicBoard> m_graphicBoard;

            std::unique_ptr<Coord> m_selection;

            std::string m_filename;
            std::string m_imageFilename;
    };
}