#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

    struct TurnTokenContainer{

        bool load(InputStream& is);

        bool isVisible = false;
    };

}  // namespace sigrid