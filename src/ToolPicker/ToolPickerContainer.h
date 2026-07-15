#pragma once

#include <string>

#include <vector>

#include "Coord/CoordBlock.h"

namespace sigrid{

struct ToolPickerContainer{
    std::vector<int> tileColorIds;
    int columns;
    int rows;
    sigrid_coord::CoordBlock miscToolBlock;
    sigrid_coord::CoordBlock colorBlock;
    std::vector<sigrid_coord::CoordBlock> pieceBlocks;
    bool show;
    bool showColors;
    std::string defaultPieceNotation;
    std::vector<std::string> toolNames;
    std::vector<int> colorToolIds;
    std::vector<std::string> pieceNotations;
    int defaultArrowColorId;
    int defaultCircleColorId;
};

}  // namespace sigrid