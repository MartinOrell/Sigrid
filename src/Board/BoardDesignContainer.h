#pragma once

#include <string>
#include <vector>
#include <istream>
#include <optional>

#include "Board/BoardLabelContainer.h"

namespace sigrid{

struct BoardDesignContainer{

    bool load(std::istream& is);

    float tileWidth = 0.f;
    float tileHeight = 0.f;
    float arrowThickness = 0.f;
    float arrowHeadSize = 0.f;
    float circleDiameter = 0.f;
    std::vector<BoardLabelContainer> labels;
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
    std::optional<sigrid::BoardLabelContainer> readLabel(std::istream& is);
};

}  // namespace sigrid