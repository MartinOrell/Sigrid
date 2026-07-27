#pragma once

#include <istream>

#include "List/Vector.h"

#include "Entity/Tile/TileContainer.h"
#include "Entity/Shape/Circle/CircleContainer.h"
#include "Entity/Shape/Arrow/ArrowContainer.h"
#include "Board/BoardLabelContainer.h"

namespace sigrid{

struct BoardDesignContainer{

    bool load(std::istream& is);

    TileContainer tile;
    CircleContainer circle;
    ArrowContainer arrow;
    sigrid_list::Vector<BoardLabelContainer> labels;
    bool border = false;
    float borderThickness = 0.f;
    bool turnToken = false;

  private:

    bool loadBorder(std::istream& is);
    bool loadTurnToken(std::istream& is);
};

}  // namespace sigrid