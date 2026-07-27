#pragma once

#include <istream>

namespace sigrid{

    struct TurnTokenContainer{

        bool load(std::istream& is);

        bool isVisible = false;
    };

}  // namespace sigrid