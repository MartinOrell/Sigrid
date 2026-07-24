#pragma once

#include <cstdint>

#include <string>
#include <vector>

#include "List/Vector.h"

#include "Window/WindowContainer.h"
#include "Entity/Piece/PieceColor.h"
#include "Entity/Piece/PieceContainer.h"
#include "Board/BoardDesignContainer.h"
#include "Menu/MenuContainer.h"
#include "ToolPicker/ToolPickerContainer.h"
#include "Tool/ToolContainer.h"

namespace sigrid_config{

struct MainConfigContainer{

    bool load(const std::string& filename);

    sigrid::WindowContainer mainWindow;
    sigrid_list::Vector<uint32_t> tileColors;
    sigrid_list::Vector<uint32_t> arrowColors;
    sigrid_list::Vector<sigrid::PieceColor> pieceColors;
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
    bool loadTileColors(std::istream& is);
    bool loadArrowColors(std::istream& is);
    bool loadPieceColors(std::istream& is);
    bool loadPieces(std::istream& is);
};

}  // namespace sigrid