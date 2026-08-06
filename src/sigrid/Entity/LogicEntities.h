#pragma once

#include <optional>

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/lists/Map.h"
#include "sigrid/utilities/Coord/Coord.h"
#include "sigrid/Entity/LogicEntity.h"
#include "sigrid/Entity/Piece/LogicPiece.h"
#include "sigrid/Entity/Shape/Circle/LogicCircle.h"

namespace sigrid{

class LogicEntities{

  public:

    LogicEntities() = default;
    LogicEntities(const LogicEntities&) = default;
    LogicEntities(LogicEntities&&) = default;
    LogicEntities& operator=(const LogicEntities&) = default;
    LogicEntities& operator=(LogicEntities&&) = default;

    sigrid_list::Vector<PieceDataContainer> getPiecesContainer() const;
    sigrid_list::Vector<CircleDataContainer> getCirclesContainer() const;

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

  private:

    sigrid_list::Map<sigrid_coord::Coord, LogicPiece> m_pieces;
    sigrid_list::Map<sigrid_coord::Coord, LogicCircle> m_circles;
    sigrid_list::Map<sigrid_coord::Coord, LogicArrow> m_arrows;
    sigrid_list::Map<sigrid_coord::Coord, LogicIcon> m_icons;
};

}  // namespace sigrid