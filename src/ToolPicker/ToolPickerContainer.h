#pragma once

#include <string>
#include <vector>
#include <istream>
#include <optional>

#include "Coord/CoordBlock.h"

namespace sigrid{

struct ToolPickerContainer{

    bool load(std::istream& is);

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

  private:
    bool loadMiscBlock(std::istream& is);
    bool loadColorBlock(std::istream& is);
    bool loadPieceBlocks(std::istream& is);
    std::optional<sigrid_coord::CoordBlock> readPieceBlock(std::istream& is);
    bool loadMiscTools(std::istream& is);
    bool loadToolColors(std::istream& is);
    bool loadToolPieces(std::istream& is);
    bool loadToolPickerTileColors(std::istream& is);
};

}  // namespace sigrid