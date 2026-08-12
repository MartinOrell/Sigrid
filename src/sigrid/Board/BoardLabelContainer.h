#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/Board/BoardLabelLocationContainer.h"

namespace sigrid{

struct BoardLabelContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    BoardLabelLocationContainer location;
    bool isVisible = false;
    float size = 0.f;
    sigrid::String font;
};

}  // namespace sigrid