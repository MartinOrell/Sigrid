#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/Coord/CoordBlock.h"

namespace sigrid{

struct ToolBlockContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    sigrid_coord::CoordBlock block;
    bool isVisible = true;
};

}  // namespace sigrid