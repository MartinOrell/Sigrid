#pragma once

#include <string>

namespace sigrid{

struct BoardLabelContainer{
    bool isInside = true;
    int position = -1; // 0 = Left, 1 = right, 2 = top, 3 = bottom
    bool isVisible = false;
    float size = 0.f;
    std::string font = "";
};

}  // namespace sigrid