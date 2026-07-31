#pragma once

#include <istream>

#include "Coord/Orientation.h"

namespace sigrid{

    struct BoardLabelLocationContainer{

        bool load(std::istream& is);

        bool isInside = true;
        sigrid_coord::Orientation orientation = sigrid_coord::Orientation::UNDEFINED;
    };

}  // namespace sigrid