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
    sigrid::MainWindowConfigContainer config;

    std::string setupFilename = "saveData/startup.txt";

    if(!std::filesystem::exists(setupFilename)){
        std::cout << "Running program with default settings" << std::endl;
        setupFilename = "res/config/defaultStartup.txt";
    }

    if(!config.load(setupFilename)){
        std::cout << "failed to load startup file: \"" << setupFilename
            << "\", exiting program" << std::endl;
        return -1;
    }

    sigrid::MainWindow mainWindow(config);

    mainWindow.run();

    std::cout << "End" << std::endl;
}