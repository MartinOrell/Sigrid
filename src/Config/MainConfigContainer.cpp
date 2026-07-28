#include "Config/MainConfigContainer.h"

#include <fstream>
#include <iostream>

#include "Config/IO.h"
#include "Config/LoadContainers.h"
#include "Color/ColorContainer.h"
#include "Config/LoadValueContainers.h"

using namespace sigrid_config;

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

            if(!loadValueContainers<sigrid::ColorContainer>(tileColors, ifs)){
                return false;
            }
        }
        else if(key == "ArrowColors:"){

            if(!loadValueContainers<sigrid::ColorContainer>(arrowColors, ifs)){
                return false;
            }
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