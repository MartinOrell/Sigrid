#pragma once

#include <cstdint>

#include <string>

#include "sigrid/Input/InputStream.h"

namespace sigrid{

struct ColorContainer{

    bool load(InputStream& is);
    bool setValue(const std::string& s);

    uint32_t value;
};

}  // namespace sigrid