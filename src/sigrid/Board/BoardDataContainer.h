#pragma once

#include <string>

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Entity/Piece/PieceDataContainer.h"
#include "sigrid/Entity/Shape/Circle/CircleDataContainer.h"

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