#pragma once

#include <cstdint>

#include <string>
#include <istream>

namespace sigrid{

struct ColorContainer{

    bool load(std::istream& is);
    bool setValue(const std::string& s);

    uint32_t value;
};

}  // namespace sigrid