#include <string>
#include <iostream>
#include <filesystem>
#include "Window/MainWindow/MainWindow.h"
#include "Window/MainWindow/MainWindowConfigContainer.h"

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