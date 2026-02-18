#pragma once

#include <string>
#include <vector>
#include "../Piece/PieceDataContainer.h"

namespace sigrid{
    struct BoardDataContainer{

        int columns;
        int rows;
        std::vector<int> repeatedSquareIds;
        std::vector<PieceDataContainer> logicPieces;
        std::string filename;
    };
}
