#pragma once

#include "sigrid/Input/InputStream.h"

namespace sigrid{

    struct ArrowContainer{

        bool load(InputStream& is);

        float thickness = 0.f;
        float headSize = 0.f;
    };

}  // namespace sigrid