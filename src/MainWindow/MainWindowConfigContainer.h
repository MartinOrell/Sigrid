#pragma once

#include <string>
#include <vector>
#include "../Piece/PieceColor.h"
#include "../Piece/PieceContainer.h"

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

        int numPieceColors;

        std::string logicBoardFilename;
        std::string graphicBoardFilename;

        bool pinMenu;
        bool toolWindow;
        bool colorTools;
    };
}
