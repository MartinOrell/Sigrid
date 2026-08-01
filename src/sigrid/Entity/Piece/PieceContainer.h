#pragma once

#include <string>

#include "sigrid/Input/InputStream.h"

namespace sigrid{

struct PieceContainer{

    bool load(InputStream& is);

    std::string name;
    std::string style;
    std::string filename;
};

}  // namespace sigrid