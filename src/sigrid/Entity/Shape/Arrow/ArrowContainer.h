#pragma once

#include <istream>

namespace sigrid{

    struct ArrowContainer{

        bool load(std::istream& is);

        float thickness = 0.f;
        float headSize = 0.f;
    };

}  // namespace sigrid