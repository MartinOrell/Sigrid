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
        else if(key == "ResetBoardFilename:"){
            ifs >> resetBoardFilename;
        }
        else if(key == "BoardFilename:"){
            ifs >> boardFilename;
        }
        else if(key == "DefaultBoardImageFilename:"){
            ifs >> defaultBoardImageFilename;
        }
        else if(key == "PinMenu:"){
            std::string s;
            ifs >> s;
            menuData.isPinned = s == "ON";
            menuData.showItems = s == "ON";
        }
        else if(key == "ToolWindow:"){
            std::string s;
            ifs >> s;
            toolWindow = s == "ON";
            menuData.showToolWindow = s == "ON";
        }
        else if(key == "ColorTools:"){
            std::string s;
            ifs >> s;
            colorTools = s == "ON";
            menuData.showColorTools = s == "ON";
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
        else if(key == "MenuFont:"){
            ifs >> menuData.fontName;
        }
        else if(key == "MenuTitle:"){
            ifs >> menuData.title;
        }
        else if(key == "MenuHeader:"){
            int headerId;
            std::string headerName;
            ifs >> headerId;
            ifs >> headerName;
            menuData.headerNames.push_back(headerName);
        }
        else if(key == "MenuItem:"){
            int itemId;
            MenuItemContainer item;
            ifs >> item.headerId;
            ifs >> itemId;
            ifs >> item.displayName;
            if(item.displayName.front() == '"'){
                while(true){    
                    std::string s;
                    ifs >> s;
                    item.displayName.append(" " + s);
                    if(s.back() == '"'){
                        break;
                    }
                }
                item.displayName.erase(0,1); //remove '"'
                item.displayName.pop_back(); //remove '"'
            }
            ifs >> item.actionName;
            menuData.menuItems.push_back(item);
        }
        else if(key == "MenuToggleItem:"){
            int itemId;
            MenuToggleItemContainer item;
            ifs >> item.headerId;
            ifs >> itemId;
            ifs >> item.keyName;
            ifs >> item.displayNameOn;
            if(item.displayNameOn.front() == '"'){
                while(true){    
                    std::string s;
                    ifs >> s;
                    item.displayNameOn.append(" " + s);
                    if(s.back() == '"'){
                        break;
                    }
                }
                item.displayNameOn.erase(0,1); //remove '"'
                item.displayNameOn.pop_back(); //remove '"'
            }
            ifs >> item.actionNameOn;
            ifs >> item.displayNameOff;
            if(item.displayNameOff.front() == '"'){
                while(true){    
                    std::string s;
                    ifs >> s;
                    item.displayNameOff.append(" " + s);
                    if(s.back() == '"'){
                        break;
                    }
                }
                item.displayNameOff.erase(0,1); //remove '"'
                item.displayNameOff.pop_back(); //remove '"'
            }
            ifs >> item.actionNameOff;
            menuData.menuToggleItems.push_back(item);
        }
        else{
            std::cout << "Unknown key: \"" << key << "\"" << std::endl;
            std::cout << "read from startup file: \"" << filename << "\"" << std::endl;
        }
    }
    return true;
}

