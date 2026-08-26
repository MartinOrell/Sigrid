#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/Color/Color.h"

namespace sigrid{

struct PieceColor{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    sigrid::String name;
    bool isLight;
    sigrid::Color lightModifier;
    sigrid::Color darkModifier;
};

}  // namespace sigrid