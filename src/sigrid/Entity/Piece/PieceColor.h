#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct PieceColor{

    bool load(InputStream& is);

    bool isLight;
    uint32_t lightModifier;
    uint32_t darkModifier;
};

}  // namespace sigrid