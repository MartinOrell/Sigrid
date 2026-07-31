#pragma once

#include <string>
#include <istream>

#include "Board/BoardLabelLocationContainer.h"

namespace sigrid{

struct BoardLabelContainer{

    bool load(std::istream& is);

    BoardLabelLocationContainer location;
    bool isVisible = false;
    float size = 0.f;
    std::string font = "";

  private:
    bool loadLocation(std::istream& is);
};

}  // namespace sigrid