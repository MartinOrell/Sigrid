#pragma once

#include <cstdint>
#include <iostream>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"

#include "sigrid/Window/WindowContainer.h"
#include "sigrid/Entity/Piece/PieceColor.h"
#include "sigrid/Entity/Piece/PieceContainer.h"
#include "sigrid/Board/BoardDesignContainer.h"
#include "sigrid/Menu/MenuContainer.h"
#include "sigrid/Window/ToolWindow/ToolWindowContainer.h"
#include "sigrid/ToolPicker/ToolPickerContainer.h"
#include "sigrid/Tool/ToolContainer.h"
#include "sigrid/Color/ColorContainer.h"

namespace sigrid_config{

struct MainConfigContainer{

    bool load(const std::string& filename);
    sigrid::String getString(const int& indentLevel);

    sigrid::WindowContainer mainWindow;
    sigrid_list::Vector<sigrid::ColorContainer> tileColors;
    sigrid_list::Vector<sigrid::ColorContainer> arrowColors;
    sigrid_list::Vector<sigrid::PieceColor> pieceColors;
    sigrid_list::Vector<sigrid::PieceContainer> pieces;
    sigrid::BoardDesignContainer boardData;
    sigrid::MenuContainer menuData;
    sigrid::ToolWindowContainer toolWindow;
    sigrid::ToolPickerContainer toolPickerData;
    sigrid::ToolContainer leftClickTool;
    sigrid::ToolContainer rightClickTool;
    sigrid::ToolContainer middleClickTool;
    sigrid::ToolContainer extra1ClickTool;
    sigrid::ToolContainer extra2ClickTool;

    sigrid::String resetBoardFilename;
    sigrid::String boardFilename;
    sigrid::String defaultBoardImageFilename;
};

}  // namespace sigrid