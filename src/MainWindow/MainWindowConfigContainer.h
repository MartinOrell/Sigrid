#pragma once

#include <string>
#include <vector>
#include "../Piece/PieceColor.h"
#include "../Piece/PieceContainer.h"
#include "../Board/BoardDesignContainer.h"
#include "../Menu/MenuContainer.h"
#include "../ToolPicker/ToolPickerContainer.h"

namespace sigrid{
    struct MainWindowConfigContainer{

        bool load(const std::string& filename);

        unsigned int windowWidth;
        unsigned int windowHeight;
        std::string windowName;

        std::vector<uint32_t> squareColors;
        std::vector<uint32_t> arrowColors;
        std::vector<PieceColor> pieceColors;
        std::vector<PieceContainer> pieces;
        BoardDesignContainer boardData;
        MenuContainer menuData;
        ToolPickerContainer toolPickerData;

        int numPieceColors;

        std::string resetBoardFilename;
        std::string boardFilename;
        std::string defaultBoardImageFilename;

        private:
            void loadWindow(std::istream& is);
            void loadSquareColors(std::istream& is);
            void loadArrowColors(std::istream& is);
    };
}
