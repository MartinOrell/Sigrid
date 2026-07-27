#pragma once

#include <istream>

namespace sigrid{

    struct CircleContainer{

        bool load(std::istream& is);

        float diameter = 0.f;
    };

}  // namespace sigrid