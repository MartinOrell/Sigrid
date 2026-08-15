#pragma once

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/String/String.h"

namespace sigrid{

struct ToolWindowContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    bool isVisible = true;
};

}  // namespace sigrid