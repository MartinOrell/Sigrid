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

        std::cerr << "MainConfigContainer: Failed to open \"" << filename << "\"."
            << " Failed to load MainConfigContainer from file: \""
            << filename << "\"" << std::endl;
        return false;
    }

    while(ifs.peek()!=EOF){

        const auto key_o = sigrid_config::readString(ifs);
        if(key_o == std::nullopt){

            std::cerr << "MainConfigContainer: Failed to read string."
                << " Failed to load MainConfigContainer from file: \""
                << filename << "\"" << std::endl;
            return false;
        }
        const std::string& key = key_o.value();
        
        if(key == "Window:"){

            if(!mainWindow.load(ifs)){

                std::cerr << "MainConfigContainer: Failed to load Window."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "TileColors:"){

            if(!loadValueContainers<sigrid::ColorContainer>(tileColors, ifs)){
                
                std::cerr << "MainConfigContainer: Failed to load tileColors."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "ArrowColors:"){

            if(!loadValueContainers<sigrid::ColorContainer>(arrowColors, ifs)){
                
                std::cerr << "MainConfigContainer: Failed to load arrowColors."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "PieceColors:"){

            if(!loadContainers<sigrid::PieceColor>(pieceColors, ifs)){
                
                std::cerr << "MainConfigContainer: Failed to load pieceColors."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "Pieces:"){

            if(!loadContainers<sigrid::PieceContainer>(pieces, ifs)){
                
                std::cerr << "MainConfigContainer: Failed to load pieces."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "BoardStyle:"){

            if(!boardData.load(ifs)){

                std::cerr << "MainConfigContainer: Failed to load boardStyle."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "Menu:"){

            if(!menuData.load(ifs)){
                
                std::cerr << "MainConfigContainer: Failed to load Menu."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "ToolPicker:"){

            if(!toolPickerData.load(ifs)){

                std::cerr << "MainConfigContainer: Failed to load toolPicker."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "LeftClickTool:"){

            if(!leftClickTool.load(ifs)){

                std::cerr << "MainConfigContainer: Failed to load leftClickTool."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "RightClickTool:"){

            if(!rightClickTool.load(ifs)){

                std::cerr << "MainConfigContainer: Failed to load rightClickTool."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "MiddleClickTool:"){

            if(!middleClickTool.load(ifs)){

                std::cerr << "MainConfigContainer: Failed to load middleClickTool."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "resetFilename:"){

            const auto resetBoardFilename_o = readString(ifs);
            if(resetBoardFilename_o == std::nullopt){

                std::cerr << "MainConfigContainer: Failed to read string for resetBoardFilename."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            resetBoardFilename = resetBoardFilename_o.value();
        }
        else if(key == "defaultImageFilename:"){

            const auto defaultBoardImageFilename_o = readString(ifs);
            if(defaultBoardImageFilename_o == std::nullopt){

                std::cerr << "MainConfigContainer: Failed to read read string for defaultBoardImageFilename."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            defaultBoardImageFilename = defaultBoardImageFilename_o.value();
        }
        else if(key == "boardFilename:"){

            const auto boardFilename_o = readString(ifs);
            if(boardFilename_o == std::nullopt){

                std::cerr << "MainConfigContainer: Failed to read string for boardFilename."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            boardFilename = boardFilename_o.value();
        }
        else{
            std::cerr << "MainConfigContainer: Unknown key: \"" << key << "\"."
                << " Failed to load MainConfigContainer from file: \""
                << filename << "\"" << std::endl;
            return false;
        }
    }
    return true;
}