#pragma once

#include <cstdint>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct ColorContainer{

    bool load(sigrid::InputStream& is);
    sigrid::String getString(const unsigned int& indentLevel) const;

    bool setValue(const sigrid::String& s);

    uint32_t value;
};

}  // namespace sigrid