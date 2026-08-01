#pragma once

#include "sigrid/Input/InputStream.h"

namespace sigrid{

    struct RectangleBorderContainer{

        bool load(InputStream& is);

        bool isVisible = false;
        float thickness = 0.f;
    };
}