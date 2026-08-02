#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct ToolContainer{

    bool load(InputStream& is);

    sigrid::String selection = "Select";
    int colorId = 0;
};

}  // namespace sigrid