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

std::string getFenFromFile(std::string filename){
    std::ifstream ifs(filename);

    assert(ifs.is_open());

    std::string out;
    ifs >> out;
    return out;
}

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

    sigrid::PieceManager pieceManager{wConfig.pieceColorFilename};
    pieceManager.loadImageFilenames(wConfig.pieceImageFilesFilename);

    auto toolPickerWindow = std::make_unique<sigrid::ToolPickerWindow>(wConfig, &pieceManager, &toolManager, wConfig.squareColors);
    toolPickerWindow->addSelectTool();
    toolPickerWindow->addArrowTool();
    for(auto notation: wConfig.pieceNotations){
        toolPickerWindow->addPieceTool(notation);
    }
    toolPickerWindow->addPieceColorTools(wConfig.numPieceColors);

    mainWindow.add(std::move(toolPickerWindow));

    auto workWindow = std::make_unique<sigrid::WorkWindow>();

    auto logicBoard = std::make_unique<sigrid::LogicBoard>(wConfig.logicBoardFilename);

    sigrid::GraphicBoardConfigContainer gConfig(wConfig.graphicBoardFilename);

    auto graphicBoard = std::make_unique<sigrid::GraphicBoard>(*logicBoard, gConfig, &pieceManager, wConfig.squareColors, &colorManager);

    auto board = std::make_unique<sigrid::Board>(std::move(logicBoard), std::move(graphicBoard), &pieceManager);


    workWindow->addBoard(std::move(board));

    mainWindow.add(std::move(workWindow));

    auto menu = std::make_unique<sigrid::Menu>(gConfig, wConfig);

    mainWindow.add(std::move(menu));



    mainWindow.run();


    std::cout << "End" << std::endl;
}