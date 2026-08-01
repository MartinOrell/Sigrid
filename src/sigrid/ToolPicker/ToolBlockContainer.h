#pragma once

#include "sigrid/Input/InputStream.h"
#include "sigrid/Coord/CoordBlock.h"

namespace sigrid{

struct ToolBlockContainer{

    bool load(InputStream& is);

    sigrid_coord::CoordBlock block;
    bool isVisible = true;
};

}  // namespace sigrid