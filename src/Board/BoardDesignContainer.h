#pragma once

#include <string>

namespace sigrid{
    struct BoardDesignContainer{

        int squareSize;
        float arrowThickness;
        float arrowHeadSize;
        float circleDiameter;
        bool labelsInside;
        bool labelsOutside;
        std::string labelFont;
        float insideLabelSize;
        float outsideLabelSize;
        bool border;
        unsigned int borderWidth;
        bool playerToMoveToken;
    };
}
