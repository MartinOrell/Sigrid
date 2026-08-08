#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct PieceContainer{

    bool load(InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const PieceContainer& piece);

    sigrid::String name;
    sigrid::String style;
    sigrid::String filename;
};

}  // namespace sigrid