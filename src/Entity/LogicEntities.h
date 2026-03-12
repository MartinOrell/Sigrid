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

            void addEntity(const Coord& coord, const LogicEntity& entity);
            void removeEntity(const Coord& coord);
            void moveEntity(const Coord& fromCoord, const Coord& toCoord);

            void clear();
            
            std::optional<LogicEntity> getEntityAt(const Coord& coord) const;

            friend std::ostream& operator<<(std::ostream& out, const LogicEntities& entities);
        private:
            std::map<Coord, LogicPiece> m_pieces;
            std::map<Coord, LogicCircle> m_circles;
    };
}
