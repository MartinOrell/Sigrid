#include "Config/MainConfigContainer.h"

#include <fstream>
#include <iostream>

#include "Config/IO.h"
#include "Config/LoadContainers.h"
#include "Color/ColorContainer.h"

using namespace sigrid_config;

bool MainConfigContainer::loadTileColors(std::istream& is){

    if(readString(is) != "["){
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){
            std::cerr << "MainConfigContainer: Failed reading string for TileColor"
                << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }

        sigrid::ColorContainer color;
        color.setValue(s);
        tileColors.push_back(color.value);
    }
    return true;
}

bool MainConfigContainer::loadArrowColors(std::istream& is){

    if(readString(is) != "["){
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){
            std::cerr << "MainConfigContainer: Failed reading string for ArrowColor"
                << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        sigrid::ColorContainer color;
        color.setValue(s);
        arrowColors.push_back(color.value);
    }
    return true;
}

bool MainConfigContainer::load(const std::string& filename){
    
    std::ifstream ifs(filename);

    if(!ifs.is_open()){
        return false;
    }

    while(ifs.peek()!=EOF){

        const auto key_o = sigrid_config::readString(ifs);
        if(key_o == std::nullopt){
            return false;
        }
        const std::string& key = key_o.value();
        
        if(key == "Window:"){
            mainWindow.load(ifs);
        }
        else if(key == "TileColors:"){
            loadTileColors(ifs);
        }
        else if(key == "ArrowColors:"){
            loadArrowColors(ifs);
        }
        else if(key == "PieceColors:"){
            loadContainers<sigrid::PieceColor>(pieceColors, ifs);
        }
        else if(key == "Pieces:"){
            loadContainers<sigrid::PieceContainer>(pieces, ifs);
        }
        else if(key == "BoardStyle:"){
            boardData.load(ifs);
        }
        else if(key == "Menu:"){
            menuData.load(ifs);
        }
        else if(key == "ToolPicker:"){
            toolPickerData.load(ifs);
        }
        else if(key == "LeftClickTool:"){
            leftClickTool.load(ifs);
        }
        else if(key == "RightClickTool:"){
            rightClickTool.load(ifs);
        }
        else if(key == "MiddleClickTool:"){
            middleClickTool.load(ifs);
        }
        else if(key == "resetFilename:"){

            const auto resetBoardFilename_o = readString(ifs);
            if(resetBoardFilename_o == std::nullopt){
                return false;
            }
            resetBoardFilename = resetBoardFilename_o.value();
        }
        else if(key == "defaultImageFilename:"){

            const auto defaultBoardImageFilename_o = readString(ifs);
            if(defaultBoardImageFilename_o == std::nullopt){
                return false;
            }
            defaultBoardImageFilename = defaultBoardImageFilename_o.value();
        }
        else if(key == "boardFilename:"){

            const auto boardFilename_o = readString(ifs);
            if(boardFilename_o == std::nullopt){
                return false;
            }
            boardFilename = boardFilename_o.value();
        }
        else{
            std::cerr << "MainConfigContainer: Unknown key: \"" << key << "\"" << std::endl;
            std::cerr << "read from startup file: \"" << filename << "\"" << std::endl;
            return false;
        }
    }
    return true;
}