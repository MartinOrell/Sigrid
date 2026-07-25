#pragma once

#include <istream>

#include "Coord/Coord.h"

namespace sigrid_coord{

struct CoordBlock{
    Coord coord;
    int columns;
    int rows;
};

}  // namespace sigrid_coord