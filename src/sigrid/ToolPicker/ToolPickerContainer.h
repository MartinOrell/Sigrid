#pragma once

#include <string>

#include "sigrid/Input/InputStream.h"
#include "sigrid/List/Vector.h"
#include "sigrid/utilities/Coord/CoordBlock.h"
#include "sigrid/ToolPicker/ToolBlockContainer.h"

namespace sigrid{

struct ToolPickerContainer{

    bool load(InputStream& is);

    sigrid_list::Vector<int> tileColorIds;
    int columns;
    int rows;
    ToolBlockContainer miscToolBlock;
    ToolBlockContainer colorBlock;
    sigrid_list::Vector<ToolBlockContainer> pieceBlocks;
    bool show;
    std::string defaultPieceNotation;
    sigrid_list::Vector<std::string> toolNames;
    sigrid_list::Vector<int> colorToolIds;
    sigrid_list::Vector<std::string> pieceNotations;
    int defaultArrowColorId;
    int defaultCircleColorId;
};

}  // namespace sigrid