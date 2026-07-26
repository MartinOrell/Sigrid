#pragma once

#include <string>

#include "List/Vector.h"
#include "Entity/Piece/PieceDataContainer.h"
#include "Entity/Shape/Circle/CircleDataContainer.h"

namespace sigrid{

struct BoardDataContainer{

    bool load(const std::string& filename);

    int columns;
    int rows;
    sigrid_list::Vector<int> repeatTileColorIds;
    sigrid_list::Vector<PieceDataContainer> logicPieces;
    sigrid_list::Vector<CircleDataContainer> logicCircles;
    std::string filename;
    std::string imageFilename;
};

}  // namespace sigrid