#pragma once

#include <string>

namespace sigrid{
    struct GraphicBoardConfigContainer{

        int squareSize;
        bool labelsInside;
        bool labelsOutside;
        std::string labelFont;
        float insideLabelSize;
        float outsideLabelSize;
        float outsideLabelSmallSize;
        float outsideLabelBigSize;
        bool border;
        unsigned int borderWidth;
        bool playerToMoveToken;
    };
}
