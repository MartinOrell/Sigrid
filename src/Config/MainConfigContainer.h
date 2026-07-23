#pragma once

#include <string>
#include <vector>

#include "Entity/Piece/PieceColor.h"
#include "Entity/Piece/PieceContainer.h"
#include "Board/BoardDesignContainer.h"
#include "Menu/MenuContainer.h"
#include "ToolPicker/ToolPickerContainer.h"
#include "Tool/ToolContainer.h"

namespace sigrid_config{

struct MainConfigContainer{

    bool load(const std::string& filename);

    int windowWidth;
    int windowHeight;
    std::string windowName;

    std::vector<uint32_t> tileColors;
    std::vector<uint32_t> arrowColors;
    std::vector<sigrid::PieceColor> pieceColors;
    std::vector<sigrid::PieceContainer> pieces;
    sigrid::BoardDesignContainer boardData;
    sigrid::MenuContainer menuData;
    sigrid::ToolPickerContainer toolPickerData;
    sigrid::ToolContainer leftClickTool;
    sigrid::ToolContainer rightClickTool;
    sigrid::ToolContainer middleClickTool;
    sigrid::ToolContainer extra1ClickTool;
    sigrid::ToolContainer extra2ClickTool;

    std::string resetBoardFilename;
    std::string boardFilename;
    std::string defaultBoardImageFilename;

  private:
    void loadWindow(std::istream& is);
    void loadTileColors(std::istream& is);
    void loadArrowColors(std::istream& is);
    void loadPieceColors(std::istream& is);
    void loadPieces(std::istream& is);
};

}  // namespace sigrid