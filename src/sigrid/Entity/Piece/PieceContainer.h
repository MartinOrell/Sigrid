#pragma once

#include <string>

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct PieceContainer{

    bool load(InputStream& is);

    std::string name;
    std::string style;
    std::string filename;
};

}  // namespace sigrid