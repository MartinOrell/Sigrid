#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <string>

#include "BoardDataContainer.h"
#include "../Coord/Coord.h"
#include "../Coord/CoordPair.h"
#include "../Entity/Tile/LogicTile.h"
#include "../Entity/Tile/LogicTiles.h"
#include "../Entity/LogicEntities.h"
#include "../Entity/Shape/Arrow/LogicArrow.h"
#include "../Entity/Shape/Arrow/LogicArrows.h"

namespace sigrid{
    class LogicBoard{

        public:
            LogicBoard();
            LogicBoard(const LogicBoard& board);
            ~LogicBoard();

            bool init(const BoardDataContainer& data);

            LogicBoard& operator=(const LogicBoard& rhs);

            const unsigned int getNumColumns() const;
            const unsigned int getNumRows() const;

            bool isWithinBoard(const Coord& coord) const;
            bool isEmptyTile(const Coord& coord) const;
            std::optional<LogicTile> getTile(const Coord& coord) const;
            std::optional<LogicEntity> getEntityAt(const Coord& coord) const;
            std::optional<LogicArrow> getArrowAt(const CoordPair& coordPair) const;
            std::string getFen() const;
            int getTurnToMove() const;

            void setTurnToMove(const int& turnToMove);

            bool addEntity(const Coord& coord, const LogicEntity& entity);
            bool removeEntity(const Coord& coord);
            bool moveEntity(const Coord& fromCoord, const Coord& toCoord);

            bool addTileHighlight(const Coord& coord, const int& highlightColorId);
            bool removeTileHighlight(const Coord& coord);

            bool addArrow(const CoordPair& coordPair, const LogicArrow& arrow);
            bool removeArrow(const CoordPair& coordPair);

            void print();
            void clearEntities();
            void clearArrows();

            friend std::ostream& operator<<(std::ostream& out, const LogicBoard& board);
        private:
            
            LogicTiles m_tileLayer;
            LogicEntities m_pieceLayer;
            LogicArrows m_arrowLayer;
            int m_turnToMove; //0 = white to move, 1 = black to move

    };
}
