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
                std::cerr << "Unknown key: \"" << s << "\"";
                std::cerr << " read in Window object" << std::endl;
            }
        }
    }
}

void MainWindowConfigContainer::loadTileColors(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            uint32_t colorHex = getColorHex(s);
            tileColors.push_back(colorHex);
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
                        std::cerr << "Unknown key: \"" << s2 << "\"";
                        std::cerr << " read in PieceColor object" << std::endl;
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
                        std::cerr << "Unknown key: \"" << s2 << "\"";
                        std::cerr << " read in Piece object" << std::endl;
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
                                    item.displayNames.push_back(s3);
                                    item.actionNames.push_back(s4);
                                    menuData.menuItems.push_back(item);
                                }
                                else{
                                    for(s4 = readString(is); s4 != "]"; s4 = readString(is)){
                                        MenuItemContainer item;
                                        item.headerId = menuData.headerNames.size()-1;
                                        item.keyName = s3;
                                        item.displayNames.push_back(s4);
                                        item.actionNames.push_back(readString(is));
                                        item.displayNames.push_back(readString(is));
                                        item.actionNames.push_back(readString(is));
                                        menuData.menuItems.push_back(item);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else{
                std::cerr << "Unknown key: \"" << s << "\"";
                std::cerr << " read in Menu object" << std::endl;
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
                        else{
                            std::cerr << "Unknown key: \"" << s2 << "\"";
                            std::cerr << " read in MiscBlock object" << std::endl;
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
                        else{
                            std::cerr << "Unknown key: \"" << s2 << "\"";
                            std::cerr << " read in ColorBlock object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "PieceBlocks:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        
                        if(s2 == "["){
                            CoordBlock pieceBlock;
                            for(std::string s3 = readString(is); s3 != "]"; s3 = readString(is)){

                                if(s3 == "visibility:"){
                                    std::string visibilityString = readString(is);
                                    bool isVisible = visibilityString == "Visible";
                                    //Currently not used
                                }
                                else if(s3 == "position:"){
                                    std::string position = readString(is);
                                    pieceBlock.coord = Coord{position};
                                }
                                else if(s3 == "columns:"){
                                    is >> pieceBlock.columns;
                                }
                                else if(s3 == "rows:"){
                                    is >> pieceBlock.rows;
                                }
                                else{
                                    std::cerr << "Unknown key: \"" << s3 << "\"";
                                    std::cerr << " read in PieceBlock object" << std::endl;
                                }
                            }
                            toolPickerData.pieceBlocks.push_back(pieceBlock);
                        }
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
            else if(s == "TileColors:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        int colorId = std::stoi(s2);
                        toolPickerData.tileColorIds.push_back(colorId);
                    }
                }
            }
            else{
                std::cerr << "Unknown key: \"" << s << "\"";
                std::cerr << " read in ToolPicker object" << std::endl;
            }
        }
    }
}

void MainWindowConfigContainer::loadBoardStyle(std::istream& is){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "Tile:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "width:"){
                            is >> boardData.tileWidth;
                        }
                        else if(s2 == "height:"){
                            is >> boardData.tileHeight;
                        }
                        else{
                            std::cerr << "Unknown key: \"" << s2 << "\"";
                            std::cerr << " read in Square object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "Arrow:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "thickness:"){
                            is >> boardData.arrowThickness;
                        }
                        else if(s2 == "headSize:"){
                            is >> boardData.arrowHeadSize;
                        }
                        else if(s2 == "defaultColorId:"){
                            is >> toolPickerData.defaultArrowColorId;
                        }
                        else{
                            std::cerr << "Unknown key: \"" << s2 << "\"";
                            std::cerr << " read in Arrow object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "Circle:"){
                std::string s2 = readString(is);
                if(s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "diameter:"){
                            is >> boardData.circleDiameter;
                        }
                        else if(s2 == "defaultColorId:"){
                            is >> toolPickerData.defaultCircleColorId;
                        }
                        else{
                            std::cerr << "Unknown key: \"" << s2 << "\"";
                            std::cerr << " read in Circle object" << std::endl;
                        }
                    }
                }
            }
            else if(s == "CoordLabels:"){
                std::string s2 = readString(is);
                if( s2 == "["){
                    for(s2 = readString(is); s2 != "]"; s2 = readString(is)){
                        if(s2 == "["){
                            BoardLabelContainer label;
                            for(std::string s3 = readString(is);s3 != "]"; s3 = readString(is)){
                                if(s3 == "position:"){
                                    std::string positionString = readString(is);
                                    label.isInside = positionString.substr(0,6) == "inside";
                                    auto spacePos = positionString.find(' ');
                                    if(spacePos != std::string::npos){
                                        std::string positionString2 = positionString.substr(spacePos+1);
                                        if(positionString2 == "left"){
                                            label.position = 0;
                                        }
                                        else if(positionString2 == "right"){
                                            label.position = 1;
                                        }
                                        else if(positionString2 == "top"){
                                            label.position = 2;
                                        }
                                        else if(positionString2 == "bottom"){
                                            label.position = 3;
                                        }
                                        else{
                                            std::cerr << "MainWindow config: Unknown label position: " << positionString2 << std::endl;
                                        }
                                    }
                                }
                                else if(s3 == "visibility:"){
                                    std::string visibilityString = readString(is);
                                    label.isVisible = visibilityString == "Visible";
                                }
                                else if(s3 == "size:"){
                                    float size;
                                    is >> size;
                                    is.ignore(1);// ignore % sign
                                    size = size/100.f;
                                    label.size = size;
                                }
                                else if(s3 == "font:"){
                                    label.font = readString(is);
                                }
                                else{
                                    std::cerr << "Unknown key: \"" << s3 << "\"";
                                    std::cerr << " read in CoordLabel object" << std::endl;
                                }
                            }
                            boardData.labels.push_back(label);
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
                            std::cerr << "Unknown key: \"" << s2 << "\"";
                            std::cerr << " read in Border object" << std::endl;
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
                            boardData.turnToken = visibilityString == "Visible";
                        }
                        else{
                            std::cerr << "Unknown key: \"" << s2 << "\"";
                            std::cerr << " read in TurnToken object" << std::endl;
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
                std::cerr << "Unknown key: \"" << s << "\"";
                std::cerr << " read in BoardStyle object" << std::endl;
            }
        }
    }
}

void MainWindowConfigContainer::loadTool(std::istream& is, ToolContainer& tool){
    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "selection:"){
                tool.selection = readString(is);
            }
            else if(s == "color:"){
                is >> tool.colorId;
            }
            else{
                std::cerr << "Unknown key: \"" << s << "\"";
                std::cerr << " read in ClickTool object" << std::endl;
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
            loadMenu(ifs);
        }
        else if(key == "ToolPicker:"){
            loadToolPicker(ifs);   
        }
        else if(key == "LeftClickTool:"){
            loadTool(ifs, leftClickTool);
        }
        else if(key == "RightClickTool:"){
            loadTool(ifs, rightClickTool);
        }
        else if(key == "MiddleClickTool:"){
            loadTool(ifs, middleClickTool);
        }
        else{
            std::cerr << "Unknown key: \"" << key << "\"" << std::endl;
            std::cerr << "read from startup file: \"" << filename << "\"" << std::endl;
        }
    }
    return true;
}

