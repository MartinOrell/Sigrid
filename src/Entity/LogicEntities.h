#pragma once

#include <optional>

#include "List/SigridMap.h"
#include "Coord/Coord.h"
#include "Entity/LogicEntity.h"
#include "Entity/Piece/LogicPiece.h"
#include "Entity/Shape/Circle/LogicCircle.h"

namespace sigrid{
    class LogicEntities{

        public:
            LogicEntities();

            void addEntity(const Coord& coord, const LogicEntity& entity);
            void removeEntity(const Coord& coord);
            void moveEntity(const Coord& fromCoord, const Coord& toCoord);

            void clear();
            
            std::optional<LogicEntity> getEntityAt(const Coord& coord) const;

            void removeColumn(const int& columnId);
            void removeRow(const int& rowId);

            void moveEntitiesRight();
            void moveEntitiesLeft();
            void moveEntitiesUp();
            void moveEntitiesDown();

            friend std::ostream& operator<<(std::ostream& out, const LogicEntities& entities);
        private:
            SigridMap<Coord, LogicPiece> m_pieces;
            SigridMap<Coord, LogicCircle> m_circles;
            SigridMap<Coord, LogicArrow> m_arrows;
            SigridMap<Coord, LogicIcon> m_icons;
    };
}
