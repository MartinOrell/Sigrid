#pragma once

#include <istream>

namespace sigrid{

struct PieceColor{

    bool load(std::istream& is);

    bool isLight;
    uint32_t lightModifier;
    uint32_t darkModifier;
};

}  // namespace sigrid