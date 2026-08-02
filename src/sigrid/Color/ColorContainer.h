#pragma once

#include <cstdint>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct ColorContainer{

    bool load(InputStream& is);
    bool setValue(const sigrid::String& s);

    uint32_t value;
};

}  // namespace sigrid