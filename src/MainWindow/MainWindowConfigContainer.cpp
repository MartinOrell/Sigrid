#include "MainWindowConfigContainer.h"

#include <fstream>
#include <iostream>

using namespace sigrid;


bool readToggle(std::istream& is){
    std::string s;
    is >> s;
    return s == "ON";
}

uint32_t readColor(std::istream& is){
    uint32_t colorHex;
    is >> std::hex >> colorHex >> std::ws;
    colorHex = colorHex * 0x100 + 0xff;
    return colorHex;
}

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
            uint32_t colorHex = readColor(ifs);
            squareColors.push_back(colorHex);
        }
        else if(key == "ArrowColor:"){
            int id;
            ifs >> id;
            uint32_t colorHex = readColor(ifs);
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
            newColor.lightModifier = readColor(ifs);
            newColor.darkModifier = readColor(ifs);
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
            menuData.isPinned = readToggle(ifs);
            menuData.showItems = menuData.isPinned;
        }
        else if(key == "ToolWindow:"){
            toolPickerData.show = readToggle(ifs);
            menuData.showToolWindow = toolPickerData.show;
        }
        else if(key == "ColorTools:"){
            toolPickerData.showColors = readToggle(ifs);
            menuData.showColorTools = toolPickerData.showColors;
        }
        else if(key == "SquareSize:"){
            ifs >> boardData.squareSize;
        }
        else if(key == "LabelsInside:"){
            boardData.labelsInside = readToggle(ifs);
        }
        else if(key == "LabelsOutside:"){
            boardData.labelsOutside = readToggle(ifs);
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
            boardData.border = readToggle(ifs);
        }
        else if(key == "BorderWidth:"){
            ifs >> boardData.borderWidth;
        }
        else if(key == "Border:"){
            boardData.border = readToggle(ifs);
        }
        else if(key == "PlayerToMoveToken:"){
            boardData.playerToMoveToken = readToggle(ifs);
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
        else if(key == "ToolPickerColumns:"){
            ifs >> toolPickerData.columns;
        }
        else if(key == "ToolPickerRows:"){
            ifs >> toolPickerData.rows;
        }
        else if(key == "ToolPickerMiscBlock:"){
            std::string coordString;
            ifs >> coordString;
            toolPickerData.miscToolBlock.coord = Coord(coordString);
            ifs >> toolPickerData.miscToolBlock.columns;
            ifs >> toolPickerData.miscToolBlock.rows;
        }
        else if(key == "ToolPickerColorBlock:"){
            std::string coordString;
            ifs >> coordString;
            toolPickerData.colorBlock.coord = Coord(coordString);
            ifs >> toolPickerData.colorBlock.columns;
            ifs >> toolPickerData.colorBlock.rows;
        }
        else if(key == "ToolPickerPieceBlock:"){
            int id;
            ifs >> id;
            std::string coordString;
            int columns;
            int rows;
            ifs >> coordString;
            ifs >> columns;
            ifs >> rows;
            CoordBlock pieceBlock{Coord{coordString},columns,rows};
            toolPickerData.pieceBlocks.push_back(pieceBlock);
        }
        else if(key == "ToolPickerTool:"){
            int id;
            ifs >> id;
            std::string toolName;
            ifs >> toolName;
            toolPickerData.toolNames.push_back(toolName);
        }
        else if(key == "ToolPickerColor:"){
            int positionId;
            int colorId;
            ifs >> positionId;
            ifs >> colorId;
            toolPickerData.colorToolIds.push_back(colorId);
        }
        else if(key == "ToolPickerDefaultPiece:"){
            ifs >> toolPickerData.defaultPieceNotation;
        }
        else if(key == "ToolPickerPiece:"){
            int id;
            ifs >> id;
            std::string notation;
            ifs >> notation;
            toolPickerData.pieceNotations.push_back(notation);
        }
        else if(key == "ToolPickerSquareColors:"){
            int positionId;
            int colorId;
            ifs >> positionId;
            ifs >> colorId;
            toolPickerData.squareColorIds.push_back(colorId);
        }
        else{
            std::cout << "Unknown key: \"" << key << "\"" << std::endl;
            std::cout << "read from startup file: \"" << filename << "\"" << std::endl;
        }
    }
    return true;
}

