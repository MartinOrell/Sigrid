#pragma once

#include <string>
#include <vector>
#include <istream>

namespace sigrid{

struct BoardLabelContainer{
    bool isInside = true;
    int position = -1; // 0 = Left, 1 = right, 2 = top, 3 = bottom
    bool isVisible = false;
    float size = 0.f;
    std::string font = "";
};

struct BoardDesignContainer{

    bool loadTile(std::istream& is);
    bool loadArrow(std::istream& is);
    bool loadCircle(std::istream& is);
    bool loadCoordLabels(std::istream& is);
    bool loadBorder(std::istream& is);
    bool loadTurnToken(std::istream& is);

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

    sigrid::BoardLabelContainer readLabel(std::istream& is);
};

}  // namespace sigrid