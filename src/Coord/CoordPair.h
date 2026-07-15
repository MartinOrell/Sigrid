#pragma once

#include <string>
#include <ostream>

#include "Coord/Coord.h"

namespace sigrid_coord{

struct CoordPair{

    Coord from;
    Coord to;

    bool operator<(const CoordPair& rhs) const;
    bool operator==(const CoordPair& rhs) const;
    bool operator!=(const CoordPair& rhs) const;

    std::string getNotation() const;
    friend std::ostream& operator<<(std::ostream& out, const CoordPair& coordPair);
};

}  // namespace sigrid_coord