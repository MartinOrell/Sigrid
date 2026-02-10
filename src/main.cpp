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

void addSquareColorsFromFile(std::vector<sf::Color>& colors, std::string filename){
    std::ifstream ifs(filename);

    assert(ifs.is_open());

    uint32_t colorHex;

    while(ifs.peek() != EOF){

        ifs >> std::hex >> colorHex >> std::ws;
        colors.push_back(sf::Color{colorHex});
    }
}

int main()
{
    sigrid::MainWindowConfigContainer wConfig("saveData/windowStartup.txt");

    sigrid::MainWindow mainWindow({wConfig.windowWidth, wConfig.windowHeight}, wConfig.windowName);

    sigrid::ColorManager colorManager{wConfig.arrowColorFilename};
    sigrid::ToolManager toolManager(&colorManager);

    auto toolWindow = std::make_unique<sigrid::ToolWindow>(&toolManager);

    mainWindow.add(std::move(toolWindow));

    sigrid::PieceManager pieceManager{wConfig.pieceColorFilename};
    pieceManager.loadImageFilenames(wConfig.pieceImageFilesFilename);

    std::vector<sf::Color> squareColors;
    addSquareColorsFromFile(squareColors, wConfig.squareColorsFileName);

    auto toolPickerWindow = std::make_unique<sigrid::ToolPickerWindow>(wConfig, &pieceManager, &toolManager, squareColors);
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

    auto graphicBoard = std::make_unique<sigrid::GraphicBoard>(*logicBoard, gConfig, &pieceManager, squareColors, &colorManager);

    auto board = std::make_unique<sigrid::Board>(std::move(logicBoard), std::move(graphicBoard), &pieceManager);


    workWindow->addBoard(std::move(board));

    mainWindow.add(std::move(workWindow));

    auto menu = std::make_unique<sigrid::Menu>(gConfig, wConfig);

    mainWindow.add(std::move(menu));



    mainWindow.run();


    std::cout << "End" << std::endl;
}