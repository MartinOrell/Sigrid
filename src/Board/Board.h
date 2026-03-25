#pragma once

#include "GraphicBoard.h"
#include "LogicBoard.h"
#include "../Entity/Piece/LogicPiece.h"
#include "../Entity/Piece/GraphicPiece.h"
#include "../Coord/Coord.h"
#include "../Entity/Piece/PieceManager.h"
#include "../Tool/Tool.h"

#include <SFML/Window/Event.hpp>

#include "../Entity/Shape/Arrow/LogicArrow.h"
#include "../Entity/Shape/Arrow/GraphicArrow.h"

#include "BoardDataContainer.h"

namespace sigrid{
    class Board: public sf::Drawable{
        public:            

            Board();

            void init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData, ColorManager* const squareColorManagerPtr, PieceManager* const pieceManagerPtr, ColorManager* const arrowColorManagerPtr);

            Board& operator=(const Board& rhs);

            void setPosition(sf::Vector2f);

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

            std::string getImageName() const;

            bool contains(sf::Vector2i point) const;

            bool isEmptySquare(const Coord& coord) const;

            bool isCoordinatesOutside() const;

            bool isWithinPlayerToMoveToken(sf::Vector2i point) const;

            bool isImageFilenameSet() const;

            std::optional<Coord> getSquareCoord(sf::Vector2i point);

            std::optional<LogicEntity> getLogicEntity(const Coord& coord);
            std::optional<GraphicEntity> getGraphicEntity(const Coord& coord);

            std::optional<LogicTile> getSquareHighlight(const Coord& coord);

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

            void addSquareHighlight(const Coord& coord, const LogicTile& newHighlight);
            void removeSquareHighlight(const Coord& coord);

            void updateDragArrow(const Coord& fromCoord, const Coord& toCoord);
            void removeDragArrow();

            void loadFen(const std::string& fen);

            void save();

            void clear();
            void print();

            void flipBoard();

            void addCoordinates();

            void removeCoordinates();

            void moveCoordinatesOutside();

            void moveCoordinatesInside();

            void setCoordinateSize(const float& size);

            void addBorder();

            void removeBorder();

            void addPlayerToMoveToken();

            void removePlayerToMoveToken();

            void togglePlayerToMoveToken();
        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<LogicBoard> m_logicBoard;

            std::unique_ptr<GraphicBoard> m_graphicBoard;

            std::unique_ptr<Coord> m_selection;

            std::string m_filename;
            std::string m_imageFilename;
    };
}