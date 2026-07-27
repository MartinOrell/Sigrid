#pragma once

#include <istream>

namespace sigrid{

    struct TileContainer{

        bool load(std::istream& is);

        float width = 0.f;
        float height = 0.f;
    };

}  // namespace sigrid