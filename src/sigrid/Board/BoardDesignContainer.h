#pragma once

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Input/InputStream.h"

#include "sigrid/Entity/Tile/TileContainer.h"
#include "sigrid/Entity/Shape/Circle/CircleContainer.h"
#include "sigrid/Entity/Shape/Arrow/ArrowContainer.h"
#include "sigrid/Board/BoardLabelContainer.h"
#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorderContainer.h"
#include "sigrid/Entity/TurnToken/TurnTokenContainer.h"

namespace sigrid{

struct BoardDesignContainer{

    bool load(InputStream& is);

    TileContainer tile;
    CircleContainer circle;
    ArrowContainer arrow;
    sigrid_list::Vector<BoardLabelContainer> labels;
    RectangleBorderContainer border;
    TurnTokenContainer turnToken;
};

}  // namespace sigrid