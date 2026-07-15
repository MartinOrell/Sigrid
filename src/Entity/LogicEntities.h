#pragma once

#include <optional>

#include "List/Map.h"
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
            sigrid_list::Map<Coord, LogicPiece> m_pieces;
            sigrid_list::Map<Coord, LogicCircle> m_circles;
            sigrid_list::Map<Coord, LogicArrow> m_arrows;
            sigrid_list::Map<Coord, LogicIcon> m_icons;
    };
}
