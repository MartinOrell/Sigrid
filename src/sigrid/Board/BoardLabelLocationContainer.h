#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/Coord/Orientation.h"

namespace sigrid{

    struct BoardLabelLocationContainer{

        bool load(InputStream& is);

        bool isInside = true;
        sigrid_coord::Orientation orientation = sigrid_coord::Orientation::UNDEFINED;
    };

}  // namespace sigrid