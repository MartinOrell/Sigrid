#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

    struct RectangleBorderContainer{

        bool load(InputStream& is);
        sigrid::String getString(const int& indentLevel) const;

        bool isVisible = false;
        float thickness = 0.f;
    };
}