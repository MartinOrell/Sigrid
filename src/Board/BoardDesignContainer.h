#pragma once

#include <string>

namespace sigrid{
    struct BoardDesignContainer{

        float tileWidth;
        float tileHeight;
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
        bool turnToken;
    };
}
