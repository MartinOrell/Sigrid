#pragma once

#include <string>
#include <vector>
#include "../Piece/LogicPieceContainer.h"

namespace sigrid{
    struct LogicBoardContainer{

        int columns;
        int rows;
        std::vector<int> repeatedSquareIds;
        std::vector<LogicPieceContainer> logicPieces;
        std::string filename;
    };
}
