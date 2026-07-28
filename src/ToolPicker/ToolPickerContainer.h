#pragma once

#include <string>
#include <istream>

#include "List/Vector.h"
#include "Coord/CoordBlock.h"
#include "ToolPicker/ToolBlockContainer.h"

namespace sigrid{

struct ToolPickerContainer{

    bool load(std::istream& is);

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

  private:
    bool loadToolPieces(std::istream& is);
};

}  // namespace sigrid