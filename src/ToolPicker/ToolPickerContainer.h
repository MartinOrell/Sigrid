#pragma once

#include <string>
#include <vector>
#include <istream>
#include <optional>

#include "Coord/CoordBlock.h"
#include "ToolPicker/ToolBlockContainer.h"

namespace sigrid{

struct ToolPickerContainer{

    bool load(std::istream& is);

    std::vector<int> tileColorIds;
    int columns;
    int rows;
    ToolBlockContainer miscToolBlock;
    ToolBlockContainer colorBlock;
    std::vector<ToolBlockContainer> pieceBlocks;
    bool show;
    std::string defaultPieceNotation;
    std::vector<std::string> toolNames;
    std::vector<int> colorToolIds;
    std::vector<std::string> pieceNotations;
    int defaultArrowColorId;
    int defaultCircleColorId;

  private:
    bool loadPieceBlocks(std::istream& is);
    bool loadMiscTools(std::istream& is);
    bool loadToolColors(std::istream& is);
    bool loadToolPieces(std::istream& is);
    bool loadToolPickerTileColors(std::istream& is);
};

}  // namespace sigrid