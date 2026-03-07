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
                std::cout << "Unknown key: \"" << s << "\"";
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

void MainWindowConfigContainer::loadArrowColors(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            uint32_t colorHex = getColorHex(s);
            arrowColors.push_back(colorHex);
        }
    }
}

void MainWindowConfigContainer::loadPieceColors(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "["){
                PieceColor pieceColor;
                for(std::string s2 = readString(is); s2 != "]"; s2 = readString(is)){
                    if(s2 == "name:"){
                        std::string name = readString(is);
                    }
                    else if(s2 == "style:"){
                        std::string style = readString(is);
                        pieceColor.isLight = style == "light";
                    }
                    else if(s2 == "lightModifier:"){
                        pieceColor.lightModifier = readColor(is);
                    }
                    else if(s2 == "darkModifier:"){
                        pieceColor.darkModifier = readColor(is);
                    }
                    else{
                        std::cout << "Unknown key: \"" << s2 << "\"";
                        std::cout << " read in PieceColor object" << std::endl;
                    }
                }
                pieceColors.push_back(pieceColor);
            }
        }
    }
}

void MainWindowConfigContainer::loadPieces(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "["){
                PieceContainer piece;
                for(std::string s2 = readString(is); s2 != "]"; s2 = readString(is)){
                    if(s2 == "notation:"){
                        piece.name = readString(is);
                    }
                    else if(s2 == "style:"){
                        piece.style = readString(is);
                    }
                    else if(s2 == "imageFilename:"){
                        piece.filename = readString(is);
                    }
                    else{
                        std::cout << "Unknown key: \"" << s2 << "\"";
                        std::cout << " read in Piece object" << std::endl;
                    }
                }
                pieces.push_back(piece);
            }
        }
    }
}

void MainWindowConfigContainer::loadMenu(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "pin:"){
                bool isPinned = readToggle(is);
                menuData.isPinned = isPinned;
                menuData.showItems = isPinned;
            }
            else if(s == "font:"){
                 menuData.fontName = readString(is);
            }
            else if(s == "title:"){
                menuData.title = readString(is);
            }
            else if(s == "headers:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        menuData.headerNames.push_back(s2);
                        std::string s3 = readString(is);
                        if(s3 == "["){
                            for(s3 = readString(is); s3 != "]"; s3 = readString(is)){
                                std::string s4 = readString(is);
                                if(s4 != "["){
                                    MenuItemContainer item;
                                    item.headerId = menuData.headerNames.size()-1;
                                    item.displayName = s3;
                                    item.actionName = s4;
                                    menuData.menuItems.push_back(item);
                                }
                                else{
                                    for(s4 = readString(is); s4 != "]"; s4 = readString(is)){
                                        MenuToggleItemContainer item;
                                        item.headerId = menuData.headerNames.size()-1;
                                        item.keyName = s3;
                                        item.displayNameOn = s4;
                                        item.actionNameOn = readString(is);
                                        item.displayNameOff = readString(is);
                                        item.actionNameOff = readString(is);
                                        menuData.menuToggleItems.push_back(item);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else{
                std::cout << "Unknown key: \"" << s << "\"";
                std::cout << " read in Menu object" << std::endl;
            }
        }
    }
}

void MainWindowConfigContainer::loadToolPicker(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "visibility:"){
                std::string visibilityString = readString(is);
                bool isVisible = visibilityString == "Visible";
                toolPickerData.show = isVisible;
                menuData.showToolWindow = isVisible;
            }
            else if(s == "columns:"){
                is >> toolPickerData.columns;
            }
            else if(s == "rows:"){
                is >> toolPickerData.rows;
            }
            else if(s == "MiscBlock:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){

                        if(s2 == "visibility:"){
                            std::string visibilityString = readString(is);
                            bool isVisible = visibilityString == "Visible";
                            //Currently not used
                        }
                        else if(s2 == "position:"){
                            std::string position = readString(is);
                            toolPickerData.miscToolBlock.coord = Coord(position);
                        }
                        else if(s2 == "columns:"){
                            is >> toolPickerData.miscToolBlock.columns;
                        }
                        else if(s2 == "rows:"){
                            is >> toolPickerData.miscToolBlock.rows;
                        }
                    }
                }
            }
            else if(s == "ColorBlock:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){

                        if(s2 == "visibility:"){
                            std::string visibilityString = readString(is);
                            bool isVisible = visibilityString == "Visible";
                            toolPickerData.showColors = isVisible;
                            menuData.showColorTools = isVisible;
                        }
                        else if(s2 == "position:"){
                            std::string position = readString(is);
                            toolPickerData.colorBlock.coord = Coord(position);
                        }
                        else if(s2 == "columns:"){
                            is >> toolPickerData.colorBlock.columns;
                        }
                        else if(s2 == "rows:"){
                            is >> toolPickerData.colorBlock.rows;
                        }
                    }
                }
            }
            else if(s == "PieceBlocks:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        std::string coordString = s2;
                        int columns;
                        int rows;
                        is >> columns;
                        is >> rows;
                        CoordBlock pieceBlock{Coord{coordString},columns,rows};
                        toolPickerData.pieceBlocks.push_back(pieceBlock);
                    }
                }
            }
            else if(s == "MiscTools:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        toolPickerData.toolNames.push_back(s2);
                    }
                }
            }
            else if(s == "Colors:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        int colorId = std::stoi(s2);
                        toolPickerData.colorToolIds.push_back(colorId);
                    }
                }
            }
            else if(s == "defaultPiece:"){
                toolPickerData.defaultPieceNotation = readString(is);
            }
            else if(s == "Pieces:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        toolPickerData.pieceNotations.push_back(s2);
                    }
                }
            }
            else if(s == "SquareColors:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        int colorId = std::stoi(s2);
                        toolPickerData.squareColorIds.push_back(colorId);
                    }
                }
            }
            else{
                std::cout << "Unknown key: \"" << s << "\"";
                std::cout << " read in ToolPicker object" << std::endl;
            }
        }
    }
}

void MainWindowConfigContainer::loadBoardStyle(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "Square:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "width:"){
                            is >> boardData.squareSize;
                        }
                        else if(s2 == "height:"){
                            int height;
                            is >> height; //Currently not used and assumed to be equal to width
                        }
                        else{
                            std::cout << "Unknown key: \"" << s2 << "\"";
                            std::cout << " read in Square object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "InsideCoordLabels:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "visibility:"){
                            std::string visibilityString = readString(is);
                            boardData.labelsInside = visibilityString == "Visible";
                        }
                        else if(s2 == "size:"){
                            float size;
                            is >> size;
                            is.ignore(1);// ignore % sign
                            size = size/100.f;
                            boardData.insideLabelSize = size;
                        }
                        else if(s2 == "font:"){
                            boardData.labelFont = readString(is);
                        }
                        else{
                            std::cout << "Unknown key: \"" << s2 << "\"";
                            std::cout << " read in InsideCoordLabel object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "OutsideCoordLabels:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "visibility:"){
                            std::string visibilityString = readString(is);
                            boardData.labelsOutside = visibilityString == "Visible";
                        }
                        else if(s2 == "size:"){
                            float size;
                            is >> size;
                            is.ignore(1);// ignore % sign
                            size = size/100.f;
                            boardData.outsideLabelSize = size;
                        }
                        else if(s2 == "font:"){
                            //Currently use same font for both inside and outside coordinates
                            boardData.labelFont = readString(is);
                        }
                        else{
                            std::cout << "Unknown key: \"" << s2 << "\"";
                            std::cout << " read in OutsideCoordLabel object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "Border:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "visibility:"){
                            std::string visibilityString = readString(is);
                            boardData.border = visibilityString == "Visible";
                        }
                        else if(s2 == "width:"){
                            is >> boardData.borderWidth;
                        }
                        else{
                            std::cout << "Unknown key: \"" << s2 << "\"";
                            std::cout << " read in Border object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "TurnToken:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "visibility:"){
                            std::string visibilityString = readString(is);
                            boardData.playerToMoveToken = visibilityString == "Visible";
                        }
                        else{
                            std::cout << "Unknown key: \"" << s2 << "\"";
                            std::cout << " read in TurnToken object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "resetFilename:"){
                resetBoardFilename = readString(is);
            }
            else if(s == "defaultImageFilename:"){
                defaultBoardImageFilename = readString(is);
            }
            else{
                std::cout << "Unknown key: \"" << s << "\"";
                std::cout << " read in BoardStyle object" << std::endl;
            }
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
            loadMenu(ifs);
        }
        else if(key == "ToolPicker:"){
            loadToolPicker(ifs);   
        }
        else{
            std::cout << "Unknown key: \"" << key << "\"" << std::endl;
            std::cout << "read from startup file: \"" << filename << "\"" << std::endl;
        }
    }
    return true;
}

