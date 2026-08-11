#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct PieceColor{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    sigrid::String name;
    bool isLight;
    uint32_t lightModifier;
    uint32_t darkModifier;
};

}  // namespace sigrid