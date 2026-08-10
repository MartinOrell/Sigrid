#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/Coord/CoordBlock.h"

namespace sigrid{

struct ToolBlockContainer{

    bool load(InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const ToolBlockContainer& toolBlockContainer);

    sigrid_coord::CoordBlock block;
    bool isVisible = true;
    int indentLevel = 0;
};

}  // namespace sigrid