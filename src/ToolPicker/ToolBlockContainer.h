#pragma once

#include <istream>

#include "Coord/CoordBlock.h"

namespace sigrid{

struct ToolBlockContainer{

    bool load(std::istream& is);

    sigrid_coord::CoordBlock block;
    bool isVisible = true;
};

}  // namespace sigrid