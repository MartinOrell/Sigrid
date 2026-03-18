#pragma once

#include <string>

#include "Coord.h"

namespace sigrid{

    struct CoordPair{

        Coord from;
        Coord to;

        bool operator<(const CoordPair& rhs) const;
        bool operator==(const CoordPair& rhs) const;
        bool operator!=(const CoordPair& rhs) const;

        std::string getNotation() const;
    };

}