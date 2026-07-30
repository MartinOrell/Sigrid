#pragma once

#include <string>
#include <istream>

#include "Coord/Orientation.h"

namespace sigrid{

struct BoardLabelContainer{

    bool load(std::istream& is);

    bool isInside = true;
    sigrid_coord::Orientation orientation = sigrid_coord::Orientation::UNDEFINED;
    bool isVisible = false;
    float size = 0.f;
    std::string font = "";

  private:
    bool loadLocation(std::istream& is);
};

}  // namespace sigrid