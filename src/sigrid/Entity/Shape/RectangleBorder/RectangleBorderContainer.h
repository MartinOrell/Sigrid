#pragma once

#include <istream>

namespace sigrid{

    struct RectangleBorderContainer{

        bool load(std::istream& is);

        bool isVisible = false;
        float thickness = 0.f;
    };
}