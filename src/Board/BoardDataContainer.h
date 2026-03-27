#pragma once

#include <string>
#include <vector>
#include "../Entity/Piece/PieceDataContainer.h"
#include "../Entity/Shape/Circle/CircleDataContainer.h"

namespace sigrid{
    struct BoardDataContainer{

        bool load(const std::string& filename);

        int columns;
        int rows;
        std::vector<int> repeatTileColorIds;
        std::vector<PieceDataContainer> logicPieces;
        std::vector<CircleDataContainer> logicCircles;
        std::string filename;
        std::string imageFilename;
    };
}
