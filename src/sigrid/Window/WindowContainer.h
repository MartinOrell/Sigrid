#pragma once

#include <string>

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

    struct WindowContainer{

        bool load(InputStream& is);

        int width;
        int height;
        std::string name;
    };
}  // namespace sigrid