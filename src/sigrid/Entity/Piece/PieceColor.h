#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct PieceColor{

    bool load(InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const PieceColor& color);

    sigrid::String name;
    bool isLight;
    uint32_t lightModifier;
    uint32_t darkModifier;
};

}  // namespace sigrid