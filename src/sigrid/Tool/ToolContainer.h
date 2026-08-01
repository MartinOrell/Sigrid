#pragma once

#include <string>

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct ToolContainer{

    bool load(InputStream& is);

    std::string selection = "Select";
    int colorId = 0;
};

}  // namespace sigrid