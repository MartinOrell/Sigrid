#pragma once

#include <string>
#include <vector>
#include "../Piece/PieceDataContainer.h"

namespace sigrid{
    struct BoardDataContainer{

        bool load(const std::string& filename);

        int columns;
        int rows;
        std::vector<int> repeatedSquareIds;
        std::vector<PieceDataContainer> logicPieces;
        std::string filename;
        std::string imageFilename;
    };
}
