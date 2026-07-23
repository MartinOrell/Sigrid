#pragma once

#include <cstdint>

#include <istream>

namespace sigrid{

struct ColorContainer{

    bool load(std::istream& is);

    uint32_t value;
};

}  // namespace sigrid