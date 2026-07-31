#pragma once

#include <string>
#include <istream>

namespace sigrid{

    struct WindowContainer{

        bool load(std::istream& is);

        int width;
        int height;
        std::string name;
    };
}  // namespace sigrid