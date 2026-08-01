#pragma once

#include <string>

#include "sigrid/Input/InputStream.h"
#include "sigrid/Board/BoardLabelLocationContainer.h"

namespace sigrid{

struct BoardLabelContainer{

    bool load(InputStream& is);

    BoardLabelLocationContainer location;
    bool isVisible = false;
    float size = 0.f;
    std::string font = "";
};

}  // namespace sigrid