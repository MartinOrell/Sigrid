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
    struct MainWindowConfigContainer{

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
    };
}
