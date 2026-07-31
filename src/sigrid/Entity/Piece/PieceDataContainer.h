#pragma once

#include <string>

namespace sigrid{

struct PieceDataContainer{

    int colorId; //0 = white, 1 = black
    std::string name; //example: N
    std::string position; //example: a2
};

}  // namespace sigrid