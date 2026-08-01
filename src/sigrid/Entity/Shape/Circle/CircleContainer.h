#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

    struct CircleContainer{

        bool load(InputStream& is);

        float diameter = 0.f;
    };

}  // namespace sigrid