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
        if(key == "WindowWidth:"){
            ifs >> windowWidth;
        }
        else if(key == "WindowHeight:"){
            ifs >> windowHeight;
        }
        else if(key == "Name:"){
            ifs >> std::ws;
            std::getline(ifs, windowName);
        }
        else if(key == "SquareColor:"){
            int id;
            ifs >> id;
            uint32_t colorHex;
            ifs >> std::hex >> colorHex >> std::ws;
            colorHex = colorHex * 0x100 + 0xff;
            squareColors.push_back(colorHex);
        }
        else if(key == "ArrowColor:"){
            int id;
            ifs >> id;
            uint32_t colorHex;
            ifs >> std::hex >> colorHex >> std::ws;
            colorHex = colorHex * 0x100 + 0xff;
            arrowColors.push_back(colorHex);
        }
        else if(key == "PieceColor:"){
            int id;
            ifs >> id;
            std::string name;
            ifs >> name;
            std::string style;
            ifs >> style;
            PieceColor newColor;
            newColor.isLight = style == "light";
            ifs >> std::hex >> newColor.lightModifier >> std::ws;
            newColor.lightModifier = newColor.lightModifier * 0x100 + 0xff;
            ifs >> std::hex >> newColor.darkModifier >> std::ws;
            newColor.darkModifier = newColor.darkModifier * 0x100 + 0xff;
            pieceColors.push_back(newColor);
        }
        else if(key == "Piece:"){
            PieceContainer piece;
            ifs >> piece.name >> piece.style >> piece.filename >> std::ws;
            pieces.push_back(piece);
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
        else if(key == "SquareSize:"){
            ifs >> boardData.squareSize;
        }
        else if(key == "LabelsInside:"){
            std::string isEnabled;
            ifs >> isEnabled;
            boardData.labelsInside = isEnabled == "ON";
        }
        else if(key == "LabelsOutside:"){
            std::string isEnabled;
            ifs >> isEnabled;
            boardData.labelsOutside = isEnabled == "ON";
        }
        else if(key == "LabelFont:"){
            ifs >> boardData.labelFont;
        }
        else if(key == "InsideLabelSize:"){
            ifs >> boardData.insideLabelSize;
            boardData.insideLabelSize = boardData.insideLabelSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "OutsideLabelSize:"){
            ifs >> boardData.outsideLabelSize;
            boardData.outsideLabelSize = boardData.outsideLabelSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "OutsideLabelSmallSize:"){
            ifs >> boardData.outsideLabelSmallSize;
            boardData.outsideLabelSmallSize = boardData.outsideLabelSmallSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "OutsideLabelBigSize:"){
            ifs >> boardData.outsideLabelBigSize;
            boardData.outsideLabelBigSize = boardData.outsideLabelBigSize / 100.f;
            ifs.ignore(1);
        }
        else if(key == "Border:"){
            std::string isEnabled;
            ifs >> isEnabled;
            boardData.border = isEnabled == "ON";
        }
        else if(key == "BorderWidth:"){
            ifs >> boardData.borderWidth;
        }
        else if(key == "Border:"){
            std::string isEnabled;
            ifs >> isEnabled;
            boardData.border = isEnabled == "ON";
        }
        else if(key == "PlayerToMoveToken:"){
            std::string isEnabled;
            ifs >> isEnabled;
            boardData.playerToMoveToken = isEnabled == "ON";
        }
        else{
            std::cout << "main: unknown key read from startupfile: " << key << std::endl;
        }
    }
    return true;
}

