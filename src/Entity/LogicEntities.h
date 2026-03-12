#pragma once

#include <map>
#include <optional>

#include "LogicEntity.h"
#include "../Piece/LogicPiece.h"
#include "../Shape/Circle/LogicCircle.h"

namespace sigrid{
    class LogicEntities{

        public:
            LogicEntities();

            void removeEntity(const Coord& coord);
            void moveEntity(const Coord& fromCoord, const Coord& toCoord);

            void addEntity(const Coord& coord, const LogicEntity& entity);

            void clear();
            
            std::optional<LogicPiece> getPieceAt(const Coord& coord) const;
            std::optional<LogicEntity> getEntityAt(const Coord& coord) const;

            bool isEmptySquare(const Coord& coord) const;

            friend std::ostream& operator<<(std::ostream& out, const LogicEntities& board);
        private:
            std::map<Coord, LogicPiece> m_pieces;
            std::map<Coord, LogicCircle> m_circles;
    };
}
