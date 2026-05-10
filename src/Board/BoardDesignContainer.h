#pragma once

#include <string>
#include <vector>

namespace sigrid{

    struct BoardLabelContainer{
        bool isInside;
        int position; // 0 = Left, 1 = right, 2 = top, 3 = bottom
        bool isVisible;
        float size;
        std::string font;
    };

    struct BoardDesignContainer{

        float tileWidth;
        float tileHeight;
        float arrowThickness;
        float arrowHeadSize;
        float circleDiameter;
        std::vector<BoardLabelContainer> labels;
        bool border;
        unsigned int borderWidth;
        bool turnToken;
    };
}
