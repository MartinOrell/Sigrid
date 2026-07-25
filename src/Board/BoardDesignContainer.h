#pragma once

#include <istream>

#include "List/Vector.h"

#include "Board/BoardLabelContainer.h"

namespace sigrid{

struct BoardDesignContainer{

    bool load(std::istream& is);

    float tileWidth = 0.f;
    float tileHeight = 0.f;
    float arrowThickness = 0.f;
    float arrowHeadSize = 0.f;
    float circleDiameter = 0.f;
    sigrid_list::Vector<BoardLabelContainer> labels;
    bool border = false;
    float borderThickness = 0.f;
    bool turnToken = false;

  private:

    bool loadTile(std::istream& is);
    bool loadArrow(std::istream& is);
    bool loadCircle(std::istream& is);
    bool loadCoordLabels(std::istream& is);
    bool loadBorder(std::istream& is);
    bool loadTurnToken(std::istream& is);
};

}  // namespace sigrid