#pragma once

#include <optional>

#include "List/OrderedMap.h"
#include "Coord/CoordPair.h"
#include "Entity/Shape/Arrow/LogicArrow.h"

namespace sigrid{

class LogicArrows{

  public:

    LogicArrows() = default;
    LogicArrows(const LogicArrows&) = default;
    LogicArrows(LogicArrows&&) = default;
    LogicArrows& operator=(const LogicArrows&) = default;
    LogicArrows& operator=(LogicArrows&&) = default;

    void addArrow(const sigrid_coord::CoordPair& coordPair, const LogicArrow& arrow);
    void removeArrow(const sigrid_coord::CoordPair& coordPair);
    
    std::optional<LogicArrow> getArrow(const sigrid_coord::CoordPair& coordPair) const;

    void removeColumn(const int& columnId);
    void removeRow(const int& rowId);

    void moveArrowsRight();
    void moveArrowsLeft();
    void moveArrowsUp();
    void moveArrowsDown();

    void clear();

  private:

    sigrid_list::OrderedMap<sigrid_coord::CoordPair, LogicArrow> m_arrows;
};

}  // namespace sigrid