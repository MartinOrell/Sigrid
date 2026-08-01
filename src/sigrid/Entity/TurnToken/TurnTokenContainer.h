#pragma once

#include "sigrid/Input/InputStream.h"

namespace sigrid{

    struct TurnTokenContainer{

        bool load(InputStream& is);

        bool isVisible = false;
    };

}  // namespace sigrid