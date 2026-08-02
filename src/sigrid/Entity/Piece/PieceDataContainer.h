#pragma once

#include "sigrid/utilities/String/String.h"

namespace sigrid{

struct PieceDataContainer{

    int colorId; //0 = white, 1 = black
    sigrid::String name; //example: N
    sigrid::String position; //example: a2
};

}  // namespace sigrid