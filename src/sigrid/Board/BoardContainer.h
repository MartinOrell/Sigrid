#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct BoardContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    sigrid::String stateFilename;
    sigrid::String imageFilename;

};

}  // namespace sigrid