#include "MainWindowConfigContainer.h"

#include <fstream>
#include <iostream>
#include <sstream>

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

uint32_t getColorHex(const std::string& s){
    uint32_t colorHex;
    std::stringstream ss;
    ss << std::hex << s;
    ss >> colorHex;
    colorHex = colorHex * 0x100 + 0xff;
    return colorHex;
}

std::string readString(std::istream& is){
    std::string s;
    is >> std::ws >> s;
    if(s.front() == '"'){
        s.erase(0,1); //remove front '"'
        while(is.peek() != EOF){    
            std::string s2;
            is >> s2;
            s.append(" " + s2);
            if(s2.back() == '"'){
                s.pop_back(); //remove back '"'
                break;
            }
        }
    }

    is >> std::ws;
    return s;
}

void MainWindowConfigContainer::loadWindow(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if (s == "Width:"){
                is >> windowWidth;
            }
            else if(s == "Height:"){
                is >> windowHeight;
            }
            else if(s == "Name:"){
                is >> windowName;
            }
            else{
                std::cout << "Unknown key: \"" << s << "\"" << std::endl;
                std::cout << " read in Window object" << std::endl;
            }
        }
    }
}

void MainWindowConfigContainer::loadSquareColors(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            uint32_t colorHex = getColorHex(s);
            squareColors.push_back(colorHex);
        }
    }
}

bool MainWindowConfigContainer::load(const std::string& filename){
    std::ifstream ifs(filename);

    if(!ifs.is_open()){
        return false;
    }

    std::string key;
    while(ifs >> key){
        if(key == "Window:"){
            loadWindow(ifs);
        }
        else if(key == "SquareColors:"){
            loadSquareColors(ifs);
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
            std::string name = readString(ifs);
            std::string style = readString(ifs);
            PieceColor newColor;
            newColor.isLight = style == "light";
            newColor.lightModifier = readColor(ifs);
            newColor.darkModifier = readColor(ifs);
            pieceColors.push_back(newColor);
        }
        else if(key == "Piece:"){
            PieceContainer piece;
            piece.name = readString(ifs);
            piece.style = readString(ifs);
            piece.filename = readString(ifs);
            pieces.push_back(piece);
        }
        else if(key == "NumPieceColors:"){
            ifs >> numPieceColors;
        }
        else if(key == "ResetBoardFilename:"){
            resetBoardFilename = readString(ifs);
        }
        else if(key == "BoardFilename:"){
            boardFilename = readString(ifs);
        }
        else if(key == "DefaultBoardImageFilename:"){
            defaultBoardImageFilename = readString(ifs);
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
            boardData.labelFont = readString(ifs);
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
            menuData.fontName = readString(ifs);
        }
        else if(key == "MenuTitle:"){
            menuData.title = readString(ifs);
        }
        else if(key == "MenuHeader:"){
            int headerId;
            ifs >> headerId;
            std::string headerName = readString(ifs);
            menuData.headerNames.push_back(headerName);
        }
        else if(key == "MenuItem:"){
            int itemId;
            MenuItemContainer item;
            ifs >> item.headerId;
            ifs >> itemId;
            item.displayName = readString(ifs);
            item.actionName = readString(ifs);
            menuData.menuItems.push_back(item);
        }
        else if(key == "MenuToggleItem:"){
            int itemId;
            MenuToggleItemContainer item;
            ifs >> item.headerId;
            ifs >> itemId;
            item.keyName = readString(ifs);
            item.displayNameOn = readString(ifs);
            item.actionNameOn = readString(ifs);
            item.displayNameOff = readString(ifs);
            item.actionNameOff = readString(ifs);
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
            std::string toolName = readString(ifs);
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
            toolPickerData.defaultPieceNotation = readString(ifs);
        }
        else if(key == "ToolPickerPiece:"){
            int id;
            ifs >> id;
            std::string notation = readString(ifs);
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

