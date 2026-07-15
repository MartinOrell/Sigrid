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

    void addEntity(const sigrid_coord::Coord& coord, const LogicEntity& entity);
    void removeEntity(const sigrid_coord::Coord& coord);
    void moveEntity(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord);

    void clear();
    
    std::optional<LogicEntity> getEntityAt(const sigrid_coord::Coord& coord) const;

    void removeColumn(const int& columnId);
    void removeRow(const int& rowId);

    void moveEntitiesRight();
    void moveEntitiesLeft();
    void moveEntitiesUp();
    void moveEntitiesDown();

    friend std::ostream& operator<<(std::ostream& out, const LogicEntities& entities);

  private:

    sigrid_list::Map<sigrid_coord::Coord, LogicPiece> m_pieces;
    sigrid_list::Map<sigrid_coord::Coord, LogicCircle> m_circles;
    sigrid_list::Map<sigrid_coord::Coord, LogicArrow> m_arrows;
    sigrid_list::Map<sigrid_coord::Coord, LogicIcon> m_icons;
};

}  // namespace sigrid