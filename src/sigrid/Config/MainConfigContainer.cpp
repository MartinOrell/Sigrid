#include "sigrid/Config/MainConfigContainer.h"

#include <fstream>
#include <iostream>

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/lists/listLoaders/LoadContainers.h"
#include "sigrid/Color/ColorContainer.h"
#include "sigrid/utilities/lists/listLoaders/LoadValueContainers.h"
#include "sigrid/utilities/lists/listSavers/ListSaver.h"

using namespace sigrid_config;

bool MainConfigContainer::load(const std::string& filename){
    
    sigrid::InputStream is;
    {
        std::ifstream ifs(filename);

        if(!ifs.is_open()){

            std::cerr << "MainConfigContainer: Failed to open \"" << filename << "\"."
                << " Failed to load MainConfigContainer from file: \""
                << filename << "\"" << std::endl;
            return false;
        }
        is.set(std::move(ifs));
    }

    while(!is.isEndOfFile()){

        const auto key_o = is.readString();
        if(key_o == std::nullopt){

            std::cerr << "MainConfigContainer: Failed to read string."
                << " Failed to load MainConfigContainer from file: \""
                << filename << "\"" << std::endl;
            return false;
        }
        const sigrid::String& key = key_o.value();
        
        if(key == "Window:"){

            if(!mainWindow.load(is)){

                std::cerr << "MainConfigContainer: Failed to load Window."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "TileColors:"){

            if(!sigrid::loadValueContainers<sigrid::ColorContainer>(tileColors, is)){
                
                std::cerr << "MainConfigContainer: Failed to load tileColors."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "ArrowColors:"){

            if(!sigrid::loadValueContainers<sigrid::ColorContainer>(arrowColors, is)){
                
                std::cerr << "MainConfigContainer: Failed to load arrowColors."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "PieceColors:"){

            if(!sigrid::loadContainers<sigrid::PieceColor>(pieceColors, is)){
                
                std::cerr << "MainConfigContainer: Failed to load pieceColors."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "Pieces:"){

            if(!sigrid::loadContainers<sigrid::PieceContainer>(pieces, is)){
                
                std::cerr << "MainConfigContainer: Failed to load pieces."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "BoardStyle:"){

            if(!boardData.load(is)){

                std::cerr << "MainConfigContainer: Failed to load boardStyle."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "Menu:"){

            if(!menuData.load(is)){
                
                std::cerr << "MainConfigContainer: Failed to load Menu."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "ToolWindow:"){

            if(!toolWindow.load(is)){

                std::cerr << "MainConfigContainer: Failed to load ToolWindow."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "ToolPicker:"){

            if(!toolPickerData.load(is)){

                std::cerr << "MainConfigContainer: Failed to load toolPicker."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "LeftClickTool:"){

            if(!leftClickTool.load(is)){

                std::cerr << "MainConfigContainer: Failed to load leftClickTool."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "RightClickTool:"){

            if(!rightClickTool.load(is)){

                std::cerr << "MainConfigContainer: Failed to load rightClickTool."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "MiddleClickTool:"){

            if(!middleClickTool.load(is)){

                std::cerr << "MainConfigContainer: Failed to load middleClickTool."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "resetFilename:"){

            const auto resetBoardFilename_o = is.readString();
            if(resetBoardFilename_o == std::nullopt){

                std::cerr << "MainConfigContainer: Failed to read string for resetBoardFilename."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            resetBoardFilename = resetBoardFilename_o.value();
        }
        else if(key == "defaultImageFilename:"){

            const auto defaultBoardImageFilename_o = is.readString();
            if(defaultBoardImageFilename_o == std::nullopt){

                std::cerr << "MainConfigContainer: Failed to read read string for defaultBoardImageFilename."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            defaultBoardImageFilename = defaultBoardImageFilename_o.value();
        }
        else if(key == "Board:"){

            if(!board.load(is)){

                std::cerr << "MainConfigContainer: Failed to load Board."
                    << " Failed to load MainConfigContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
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

sigrid::String sigrid_config::MainConfigContainer::getString(const int& indentLevel){

    sigrid::String indent0;

    for(int i = 0; i < indentLevel; i++){
        indent0.append("  ");
    }

    sigrid::String out;

    out.append("Window: ");
    out.append(this->mainWindow.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("TileColors: ");
    out.append(sigrid::ListSaver(this->tileColors).getMultiLineString(indentLevel));
    
    out.append("\n");
    out.append(indent0);
    out.append("ArrowColors: ");
    out.append(sigrid::ListSaver(this->arrowColors).getMultiLineString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("PieceColors: ");
    out.append(sigrid::ListSaver(this->pieceColors).getMultiLineString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("Pieces: ");
    out.append(sigrid::ListSaver(this->pieces).getMultiLineString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("LeftClickTool: ");
    out.append(this->leftClickTool.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("RightClickTool: ");
    out.append(this->rightClickTool.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("MiddleClickTool: ");
    out.append(this->middleClickTool.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("Menu: ");
    out.append(this->menuData.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("ToolWindow: ");
    out.append(this->toolWindow.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("ToolPicker: ");
    out.append(this->toolPickerData.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("BoardStyle: ");
    out.append(this->boardData.getString(indentLevel));

    out.append("\n");
    out.append(indent0);
    out.append("resetFilename: ");
    out.append(this->resetBoardFilename);

    out.append("\n");
    out.append(indent0);
    out.append("defaultImageFilename: ");
    out.append(this->defaultBoardImageFilename);

    out.append("\n");
    out.append(indent0);
    out.append("Board: ");
    out.append(this->board.getString(indentLevel));

    return out;
}