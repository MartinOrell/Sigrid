#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct ToolContainer{

    bool load(InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const ToolContainer& tool);

    sigrid::String selection = "Select";
    int colorId = 0;
};

}  // namespace sigrid