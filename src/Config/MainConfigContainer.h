#pragma once

#include <string>
#include <vector>

#include "Entity/Piece/PieceColor.h"
#include "Entity/Piece/PieceContainer.h"
#include "Board/BoardDesignContainer.h"
#include "Menu/MenuContainer.h"
#include "ToolPicker/ToolPickerContainer.h"
#include "Tool/ToolContainer.h"

namespace sigrid{

struct MainConfigContainer{

    bool load(const std::string& filename);

    int windowWidth;
    int windowHeight;
    std::string windowName;

    std::vector<uint32_t> tileColors;
    std::vector<uint32_t> arrowColors;
    std::vector<PieceColor> pieceColors;
    std::vector<PieceContainer> pieces;
    BoardDesignContainer boardData;
    MenuContainer menuData;
    ToolPickerContainer toolPickerData;
    ToolContainer leftClickTool;
    ToolContainer rightClickTool;
    ToolContainer middleClickTool;
    ToolContainer extra1ClickTool;
    ToolContainer extra2ClickTool;

    std::string resetBoardFilename;
    std::string boardFilename;
    std::string defaultBoardImageFilename;

  private:
    void loadWindow(std::istream& is);
    void loadTileColors(std::istream& is);
    void loadArrowColors(std::istream& is);
    void loadPieceColors(std::istream& is);
    void loadPieces(std::istream& is);
    void loadMenu(std::istream& is);
    void loadToolPicker(std::istream& is);
    void loadBoardStyle(std::istream& is);
    void loadTool(std::istream& is, ToolContainer& tool);

    PieceColor readPieceColor(std::istream& is);

    void loadHeaders(std::istream& is);
    void loadHeaderItems(std::istream& is);
    void loadMenuItem(std::istream&is, const std::string& displayName);

    void loadMiscBlock(std::istream& is);
    void loadColorBlock(std::istream& is);
    void loadPieceBlocks(std::istream& is);
    sigrid_coord::CoordBlock readPieceBlock(std::istream& is);
    void loadMiscTools(std::istream& is);
    void loadToolColors(std::istream& is);
    void loadToolPieces(std::istream& is);
    void loadToolPickerTileColors(std::istream& is);

    void loadTile(std::istream& is);
    void loadArrow(std::istream& is);
    void loadCircle(std::istream& is);
    void loadCoordLabels(std::istream& is);
    BoardLabelContainer readLabel(std::istream& is);
    void loadBorder(std::istream& is);
    void loadTurnToken(std::istream& is);
};

}  // namespace sigrid