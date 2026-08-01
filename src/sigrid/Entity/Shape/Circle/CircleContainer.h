#pragma once

#include "sigrid/Input/InputStream.h"

namespace sigrid{

    struct CircleContainer{

        bool load(InputStream& is);

        float diameter = 0.f;
    };

}  // namespace sigrid