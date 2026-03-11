#pragma once

#include <map>
#include <optional>

#include "../Piece/LogicPiece.h"
#include "../Shape/Circle/LogicCircle.h"

namespace sigrid{
    class LogicEntities{

        public:
            LogicEntities();

            void addPiece(const Coord& coord, const LogicPiece& logicPiece);
            void addCircle(const Coord& coord, const LogicCircle& logicCircle);

            void removePiece(const Coord& coord);
            void removeCircle(const Coord& coord);

            void clear();
            
            std::optional<LogicPiece> getPieceAt(const Coord& coord) const;
            std::optional<LogicCircle> getCircleAt(const Coord& coord) const;

            bool isEmptySquare(const Coord& coord) const;

            friend std::ostream& operator<<(std::ostream& out, const LogicEntities& board);
        private:
            std::map<Coord, LogicPiece> m_pieces;
            std::map<Coord, LogicCircle> m_circles;
    };
}
