#include "MainWindow/MainWindow.h"
#include "Menu/Menu.h"
#include "WorkWindow/WorkWindow.h"
#include "ToolWindow/ToolWindow.h"
#include <string>
#include "Piece/PieceManager.h"
#include "Menu/MenuItem.h"
#include "Action/Action.h"
#include <fstream>
#include <iostream>
#include <filesystem>

#include "Tool/Tool.h"

#include "ToolPicker/ToolPickerWindow.h"

#include "Tool/ToolManager.h"

#include "Color/ColorManager.h"

#include "Board/LogicBoard.h"

#include "MainWindow/MainWindowConfigContainer.h"

#include "Board/LogicBoardContainer.h"
#include "Piece/LogicPieceContainer.h"

int main()
{
    sigrid::MainWindowConfigContainer wConfig;

    std::string setupFilename = "saveData/startup.txt";

    if(!std::filesystem::exists(setupFilename)){
        std::cout << "Running program with default settings" << std::endl;
        setupFilename = "res/config/defaultStartup.txt";
    }

    if(!wConfig.load(setupFilename)){
        std::cout << "failed to load startup file: \"" << setupFilename
            << "\", exiting program" << std::endl;
        return -1;
    }

    sigrid::MainWindow mainWindow({wConfig.windowWidth, wConfig.windowHeight}, wConfig.windowName);

    sigrid::ColorManager colorManager{wConfig.arrowColors};
    
    sigrid::ToolManager toolManager(&colorManager);

    auto toolWindow = std::make_unique<sigrid::ToolWindow>(&toolManager);

    mainWindow.add(std::move(toolWindow));

    sigrid::PieceManager pieceManager{wConfig.pieceColors};
    pieceManager.loadImages(wConfig.pieces);

    auto toolPickerWindow = std::make_unique<sigrid::ToolPickerWindow>(wConfig, &pieceManager, &toolManager, wConfig.squareColors);
    toolPickerWindow->addSelectTool();
    toolPickerWindow->addArrowTool();
    for(const auto& piece: wConfig.pieces){
        if(piece.style == "light"){
            toolPickerWindow->addPieceTool(piece.name);
        }
    }
    toolPickerWindow->addPieceColorTools(wConfig.numPieceColors);

    mainWindow.add(std::move(toolPickerWindow));

    auto workWindow = std::make_unique<sigrid::WorkWindow>();

    auto board = std::make_unique<sigrid::Board>(wConfig.boardFilename, wConfig.boardData, wConfig.squareColors, &pieceManager, &colorManager);

    workWindow->addBoard(std::move(board));

    mainWindow.add(std::move(workWindow));

    auto menu = std::make_unique<sigrid::Menu>(wConfig.boardData, wConfig);

    mainWindow.add(std::move(menu));



    mainWindow.run();


    std::cout << "End" << std::endl;
}