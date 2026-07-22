#pragma once

#include <string>
#include <istream>

namespace sigrid{

struct PieceContainer{

    bool load(std::istream& is);

    std::string name;
    std::string style;
    std::string filename;
};

}  // namespace sigrid