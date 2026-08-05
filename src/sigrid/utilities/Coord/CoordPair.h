#pragma once

#include <ostream>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/Coord/Coord.h"

namespace sigrid_coord{

struct CoordPair{

    CoordPair() = default;
    CoordPair(const CoordPair&) = default;
    CoordPair(CoordPair&&) = default;
    CoordPair& operator=(const CoordPair&) = default;
    CoordPair& operator=(CoordPair&&) = default;

    CoordPair(const Coord& from, const Coord& to);
    CoordPair(const sigrid::String& notation);

    bool operator<(const CoordPair& rhs) const;
    bool operator==(const CoordPair& rhs) const;
    bool operator!=(const CoordPair& rhs) const;

    bool set(const sigrid::String& notation);

    sigrid::String getNotation() const;
    friend std::ostream& operator<<(std::ostream& out, const CoordPair& coordPair);

    Coord from;
    Coord to;
};

}  // namespace sigrid_coord