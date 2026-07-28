#pragma once

#include <cstdint>

#include <string>

#include "List/Vector.h"

#include "Window/WindowContainer.h"
#include "Entity/Piece/PieceColor.h"
#include "Entity/Piece/PieceContainer.h"
#include "Board/BoardDesignContainer.h"
#include "Menu/MenuContainer.h"
#include "ToolPicker/ToolPickerContainer.h"
#include "Tool/ToolContainer.h"
#include "Color/ColorContainer.h"

namespace sigrid_config{

struct MainConfigContainer{

    bool load(const std::string& filename);

    sigrid::WindowContainer mainWindow;
    sigrid_list::Vector<sigrid::ColorContainer> tileColors;
    sigrid_list::Vector<sigrid::ColorContainer> arrowColors;
    sigrid_list::Vector<sigrid::PieceColor> pieceColors;
    sigrid_list::Vector<sigrid::PieceContainer> pieces;
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
};

}  // namespace sigrid