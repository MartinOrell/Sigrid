#pragma once

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/InputStream/InputStream.h"

#include "sigrid/Entity/Tile/TileContainer.h"
#include "sigrid/Entity/Shape/Circle/CircleContainer.h"
#include "sigrid/Entity/Shape/Arrow/ArrowContainer.h"
#include "sigrid/Board/BoardLabelContainer.h"
#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorderContainer.h"
#include "sigrid/Entity/TurnToken/TurnTokenContainer.h"

namespace sigrid{

struct BoardDesignContainer{

    bool load(InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const BoardDesignContainer& boardStyle);

    TileContainer tile;
    CircleContainer circle;
    ArrowContainer arrow;
    sigrid_list::Vector<BoardLabelContainer> labels;
    RectangleBorderContainer border;
    TurnTokenContainer turnToken;
};

}  // namespace sigrid