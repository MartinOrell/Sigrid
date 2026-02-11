#include "MainWindowConfigContainer.h"

#include <fstream>
#include <iostream>

using namespace sigrid;


bool MainWindowConfigContainer::load(const std::string& filename){
    std::ifstream ifs(filename);

    if(!ifs.is_open()){
        return false;
    }

    std::string key;
    while(ifs >> key){
        if(key == "Width:"){
            ifs >> windowWidth;
        }
        else if(key == "Height:"){
            ifs >> windowHeight;
        }
        else if(key == "Name:"){
            ifs >> std::ws;
            std::getline(ifs, windowName);
        }
        else if(key == "ArrowColor:"){
            int id;
            ifs >> id;
            uint32_t colorHex;
            ifs >> std::hex >> colorHex >> std::ws;
            colorHex = colorHex * 0x100 + 0xff;
            arrowColors.push_back(colorHex);
        }
        else if(key == "PieceColors:"){
            ifs >> pieceColorFilename;
        }
        else if(key == "PieceImageFiles:"){
            ifs >> pieceImageFilesFilename;
        }
        else if(key == "SquareColors:"){
            ifs >> squareColorsFileName;
        }
        else if(key == "Piece:"){
            std::string pieceNotation;
            ifs >> pieceNotation;
            pieceNotations.push_back(pieceNotation);
        }
        else if(key == "NumPieceColors:"){
            ifs >> numPieceColors;
        }
        else if(key == "LogicBoardFilename:"){
            ifs >> logicBoardFilename;
        }
        else if(key == "GraphicBoardFilename:"){
            ifs >> graphicBoardFilename;
        }
        else if(key == "PinMenu:"){
            std::string s;
            ifs >> s;
            pinMenu = s == "ON";
        }
        else if(key == "ToolWindow:"){
            std::string s;
            ifs >> s;
            toolWindow = s == "ON";
        }
        else if(key == "ColorTools:"){
            std::string s;
            ifs >> s;
            colorTools = s == "ON";
        }
        else{
            std::cout << "main: unknown key read from startupfile: " << key << std::endl;
        }
    }
    return true;
}

