#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct PieceContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    sigrid::String name;
    sigrid::String style;
    sigrid::String filename;
};

}  // namespace sigrid