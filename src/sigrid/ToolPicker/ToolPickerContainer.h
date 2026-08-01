#pragma once

#include <string>

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/lists/Vector.h"
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