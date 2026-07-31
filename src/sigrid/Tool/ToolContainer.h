#pragma once

#include <string>
#include <istream>

namespace sigrid{

struct ToolContainer{

    bool load(std::istream& is);

    std::string selection = "Select";
    int colorId = 0;
};

}  // namespace sigrid