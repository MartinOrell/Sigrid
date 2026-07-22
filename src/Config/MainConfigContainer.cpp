#include "Config/MainConfigContainer.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "Config/IO.h"

using namespace sigrid_config;

uint32_t readColor(std::istream& is){

    uint32_t colorHex;
    is >> std::hex >> colorHex >> std::ws;
    colorHex = colorHex * 0x100 + 0xff;
    return colorHex;
}

uint32_t getColorHex(const std::string& s){

    uint32_t colorHex;
    std::stringstream ss;
    ss << std::hex << s;
    ss >> colorHex;
    colorHex = colorHex * 0x100 + 0xff;
    return colorHex;
}

void MainConfigContainer::loadWindow(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if (s == "width:"){
                is >> windowWidth;
            }
            else if(s == "height:"){
                is >> windowHeight;
            }
            else if(s == "name:"){
                is >> windowName;
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in Window object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadTileColors(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            uint32_t colorHex = getColorHex(s);
            tileColors.push_back(colorHex);
        }
    }
}

void MainConfigContainer::loadArrowColors(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            uint32_t colorHex = getColorHex(s);
            arrowColors.push_back(colorHex);
        }
    }
}

void MainConfigContainer::loadPieceColors(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "["){
                sigrid::PieceColor pieceColor = readPieceColor(is);
                pieceColors.push_back(pieceColor);
            }
        }
    }
}

void MainConfigContainer::loadPieces(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "["){
                sigrid::PieceContainer piece;
                if(piece.load(is)){
                    pieces.push_back(piece);
                }
            }
        }
    }
}

void MainConfigContainer::loadBoardStyle(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "Tile:"){
                boardData.loadTile(is);
            }
            else if(s == "Arrow:"){
                boardData.loadArrow(is, toolPickerData.defaultArrowColorId);
            }
            else if(s == "Circle:"){
                boardData.loadCircle(is, toolPickerData.defaultCircleColorId);
            }
            else if(s == "CoordLabels:"){
                boardData.loadCoordLabels(is);
            }
            else if(s == "Border:"){
                boardData.loadBorder(is);
            }
            else if(s == "TurnToken:"){
                boardData.loadTurnToken(is);
            }
            else if(s == "resetFilename:"){
                resetBoardFilename = readString(is);
            }
            else if(s == "defaultImageFilename:"){
                defaultBoardImageFilename = readString(is);
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in BoardStyle object" << std::endl;
            }
        }
    }
}

bool MainConfigContainer::load(const std::string& filename){
    
    std::ifstream ifs(filename);

    if(!ifs.is_open()){
        return false;
    }

    std::string key;
    while(ifs >> key){
        if(key == "Window:"){
            loadWindow(ifs);
        }
        else if(key == "TileColors:"){
            loadTileColors(ifs);
        }
        else if(key == "ArrowColors:"){
            loadArrowColors(ifs);
        }
        else if(key == "PieceColors:"){
            loadPieceColors(ifs);
        }
        else if(key == "Pieces:"){
            loadPieces(ifs);
        }
        else if(key == "boardFilename:"){
            boardFilename = readString(ifs);
        }
        else if(key == "BoardStyle:"){
            loadBoardStyle(ifs);
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
        else{
            std::cerr << "MainWindowConfigContainer: Unknown key: \"" << key << "\"" << std::endl;
            std::cerr << "read from startup file: \"" << filename << "\"" << std::endl;
        }
    }
    return true;
}

sigrid::PieceColor MainConfigContainer::readPieceColor(std::istream& is){

    sigrid::PieceColor pieceColor;
    for(std::string s = readString(is); s != "]"; s = readString(is)){
        if(s == "name:"){
            std::string name = readString(is);
        }
        else if(s == "style:"){
            std::string style = readString(is);
            pieceColor.isLight = style == "light";
        }
        else if(s == "lightModifier:"){
            pieceColor.lightModifier = readColor(is);
        }
        else if(s == "darkModifier:"){
            pieceColor.darkModifier = readColor(is);
        }
        else{
            std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
            std::cerr << " read in PieceColor object" << std::endl;
        }
    }
    return pieceColor;
}