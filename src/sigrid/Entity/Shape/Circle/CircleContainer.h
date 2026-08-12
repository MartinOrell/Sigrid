#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct CircleContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel);

    float diameter = 0.f;
};

}  // namespace sigrid