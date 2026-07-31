#pragma once

#include <string>
#include <istream>

#include "sigrid/Board/BoardLabelLocationContainer.h"

namespace sigrid{

struct BoardLabelContainer{

    bool load(std::istream& is);

    BoardLabelLocationContainer location;
    bool isVisible = false;
    float size = 0.f;
    std::string font = "";
};

}  // namespace sigrid