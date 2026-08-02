#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

    struct WindowContainer{

        bool load(InputStream& is);

        int width;
        int height;
        sigrid::String name;
    };
}  // namespace sigrid