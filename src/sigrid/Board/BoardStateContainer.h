#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Entity/Piece/PieceDataContainer.h"
#include "sigrid/Entity/Shape/Circle/CircleDataContainer.h"
#include "sigrid/Entity/Shape/Arrow/ArrowDataContainer.h"

namespace sigrid{

struct BoardStateContainer{

    bool load(const sigrid::String& filename);
    friend std::ostream& operator<<(std::ostream& out, const BoardStateContainer& boardState);

    int columns;
    int rows;
    sigrid_list::Vector<int> repeatTileColorIds;
    sigrid_list::Vector<PieceDataContainer> logicPieces;
    sigrid_list::Vector<CircleDataContainer> logicCircles;
    sigrid_list::Vector<ArrowDataContainer> logicArrows;
};

}  // namespace sigrid