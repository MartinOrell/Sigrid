#pragma once

#include <string>
#include <istream>

namespace sigrid{

struct BoardLabelContainer{

    bool load(std::istream& is);

    bool isInside = true;
    int position = -1; // 0 = Left, 1 = right, 2 = top, 3 = bottom
    bool isVisible = false;
    float size = 0.f;
    std::string font = "";

  private:
    bool loadLocation(std::istream& is);
};

}  // namespace sigrid