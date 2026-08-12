#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct TurnTokenContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    bool isVisible = false;
};

}  // namespace sigrid