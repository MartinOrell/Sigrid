#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

    struct TileContainer{

        bool load(InputStream& is);

        float width = 0.f;
        float height = 0.f;
    };

}  // namespace sigrid