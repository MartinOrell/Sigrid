#pragma once

#include <istream>

#include "List/Vector.h"

#include "Entity/Tile/TileContainer.h"
#include "Entity/Shape/Circle/CircleContainer.h"
#include "Entity/Shape/Arrow/ArrowContainer.h"
#include "Board/BoardLabelContainer.h"
#include "Entity/Shape/RectangleBorder/RectangleBorderContainer.h"
#include "Entity/TurnToken/TurnTokenContainer.h"

namespace sigrid{

struct BoardDesignContainer{

    bool load(std::istream& is);

    TileContainer tile;
    CircleContainer circle;
    ArrowContainer arrow;
    sigrid_list::Vector<BoardLabelContainer> labels;
    RectangleBorderContainer border;
    TurnTokenContainer turnToken;
};

}  // namespace sigrid