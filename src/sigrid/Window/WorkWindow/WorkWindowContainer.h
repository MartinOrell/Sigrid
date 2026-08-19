#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct WorkWindowContainer{

    bool load(sigrid::InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    int boardColumns = 1;
    int boardRows = 1;
};

}  // namespace sigrid