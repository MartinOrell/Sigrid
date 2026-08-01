#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

    struct RectangleBorderContainer{

        bool load(InputStream& is);

        bool isVisible = false;
        float thickness = 0.f;
    };
}