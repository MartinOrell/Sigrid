#pragma once

#include "Coord/Orientation.h"

namespace sigrid{

    struct BoardLabelLocationContainer{

        bool isInside = true;
        sigrid_coord::Orientation orientation = sigrid_coord::Orientation::UNDEFINED;
    };

}  // namespace sigrid