#include "Config/MainConfigContainer.h"

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
                PieceColor pieceColor = readPieceColor(is);
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
                PieceContainer piece;
                if(piece.load(is)){
                    pieces.push_back(piece);
                }
            }
        }
    }
}

void MainConfigContainer::loadMenu(std::istream& is){

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
                loadHeaders(is);
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in Menu object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadToolPicker(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "visibility:"){
                std::string visibilityString = readString(is);
                bool isVisible = visibilityString == "Visible";
                toolPickerData.show = isVisible;
            }
            else if(s == "columns:"){
                is >> toolPickerData.columns;
            }
            else if(s == "rows:"){
                is >> toolPickerData.rows;
            }
            else if(s == "MiscBlock:"){
                loadMiscBlock(is);
            }
            else if(s == "ColorBlock:"){
                loadColorBlock(is);
            }
            else if(s == "PieceBlocks:"){
                loadPieceBlocks(is);
            }
            else if(s == "MiscTools:"){
                loadMiscTools(is);
                
            }
            else if(s == "Colors:"){
                loadToolColors(is);
                
            }
            else if(s == "defaultPiece:"){
                toolPickerData.defaultPieceNotation = readString(is);
            }
            else if(s == "Pieces:"){
                loadToolPieces(is);
            }
            else if(s == "TileColors:"){
                loadToolPickerTileColors(is);
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in ToolPicker object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadBoardStyle(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "Tile:"){
                loadTile(is);
            }
            else if(s == "Arrow:"){
                loadArrow(is);
            }
            else if(s == "Circle:"){
                loadCircle(is);
            }
            else if(s == "CoordLabels:"){
                loadCoordLabels(is);
            }
            else if(s == "Border:"){
                loadBorder(is);
            }
            else if(s == "TurnToken:"){
                loadTurnToken(is);
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

void MainConfigContainer::loadTool(std::istream& is, ToolContainer& tool){

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
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in ClickTool object" << std::endl;
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
            std::cerr << "MainWindowConfigContainer: Unknown key: \"" << key << "\"" << std::endl;
            std::cerr << "read from startup file: \"" << filename << "\"" << std::endl;
        }
    }
    return true;
}

PieceColor MainConfigContainer::readPieceColor(std::istream& is){

    PieceColor pieceColor;
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

void MainConfigContainer::loadHeaders(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            menuData.headerNames.push_back(s);
            loadHeaderItems(is);
        }
    }
}

void MainConfigContainer::loadHeaderItems(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            loadMenuItem(is, s);
        }
    }
}

void MainConfigContainer::loadMenuItem(std::istream& is, const std::string& displayName){

    std::string s = readString(is);
    if(s != "["){
        MenuItemContainer item;
        item.headerId = menuData.headerNames.size()-1;
        item.displayNames.push_back(displayName);
        item.actionNames.push_back(s);
        menuData.menuItems.push_back(item);
    }
    else{
        for(s = readString(is); s != "]"; s = readString(is)){
            MenuItemContainer item;
            item.headerId = menuData.headerNames.size()-1;
            item.keyName = displayName;
            item.displayNames.push_back(s);
            item.actionNames.push_back(readString(is));
            item.displayNames.push_back(readString(is));
            item.actionNames.push_back(readString(is));
            menuData.menuItems.push_back(item);
        }
    }
}

void MainConfigContainer::loadMiscBlock(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){

            if(s == "visibility:"){
                std::string visibilityString = readString(is);
                bool isVisible = visibilityString == "Visible";
                //Currently not used
            }
            else if(s == "position:"){
                std::string position = readString(is);
                toolPickerData.miscToolBlock.coord = sigrid_coord::Coord(position);
            }
            else if(s == "columns:"){
                is >> toolPickerData.miscToolBlock.columns;
            }
            else if(s == "rows:"){
                is >> toolPickerData.miscToolBlock.rows;
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in MiscBlock object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadColorBlock(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){

            if(s == "visibility:"){
                std::string visibilityString = readString(is);
                bool isVisible = visibilityString == "Visible";
                toolPickerData.showColors = isVisible;
            }
            else if(s == "position:"){
                std::string position = readString(is);
                toolPickerData.colorBlock.coord = sigrid_coord::Coord(position);
            }
            else if(s == "columns:"){
                is >> toolPickerData.colorBlock.columns;
            }
            else if(s == "rows:"){
                is >> toolPickerData.colorBlock.rows;
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in ColorBlock object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadPieceBlocks(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "["){
                sigrid_coord::CoordBlock pieceBlock = readPieceBlock(is);
                toolPickerData.pieceBlocks.push_back(pieceBlock);
            }
        }
    }
}

sigrid_coord::CoordBlock MainConfigContainer::readPieceBlock(std::istream& is){

    sigrid_coord::CoordBlock pieceBlock;
    for(std::string s = readString(is); s != "]"; s = readString(is)){

        if(s == "visibility:"){
            std::string visibilityString = readString(is);
            bool isVisible = visibilityString == "Visible";
            //Currently not used
        }
        else if(s == "position:"){
            std::string position = readString(is);
            pieceBlock.coord = sigrid_coord::Coord{position};
        }
        else if(s == "columns:"){
            is >> pieceBlock.columns;
        }
        else if(s == "rows:"){
            is >> pieceBlock.rows;
        }
        else{
            std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
            std::cerr << " read in PieceBlock object" << std::endl;
        }
    }
    return pieceBlock;
}

void MainConfigContainer::loadMiscTools(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            toolPickerData.toolNames.push_back(s);
        }
    }
}

void MainConfigContainer::loadToolColors(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            int colorId = std::stoi(s);
            toolPickerData.colorToolIds.push_back(colorId);
        }
    }
}

void MainConfigContainer::loadToolPieces(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            toolPickerData.pieceNotations.push_back(s);
        }
    }
}

void MainConfigContainer::loadToolPickerTileColors(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            int colorId = std::stoi(s);
            toolPickerData.tileColorIds.push_back(colorId);
        }
    }
}

void MainConfigContainer::loadTile(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "width:"){
                is >> boardData.tileWidth;
            }
            else if(s == "height:"){
                is >> boardData.tileHeight;
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in Square object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadArrow(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "thickness:"){
                is >> boardData.arrowThickness;
            }
            else if(s == "headSize:"){
                is >> boardData.arrowHeadSize;
            }
            else if(s == "defaultColorId:"){
                is >> toolPickerData.defaultArrowColorId;
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in Arrow object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadCircle(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "diameter:"){
                is >> boardData.circleDiameter;
            }
            else if(s == "defaultColorId:"){
                is >> toolPickerData.defaultCircleColorId;
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in Circle object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadCoordLabels(std::istream& is){

    std::string s = readString(is);
    if( s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "["){
                BoardLabelContainer label = readLabel(is);
                boardData.labels.push_back(label);
            }
        }
    }
}

BoardLabelContainer MainConfigContainer::readLabel(std::istream& is){

    BoardLabelContainer label;
    for(std::string s = readString(is);s != "]"; s = readString(is)){
        if(s == "position:"){
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
                    std::cerr << "MainWindowConfigContainer: Unknown label position: " << positionString2 << std::endl;
                }
            }
        }
        else if(s == "visibility:"){
            std::string visibilityString = readString(is);
            label.isVisible = visibilityString == "Visible";
        }
        else if(s == "size:"){
            float size;
            is >> size;
            is.ignore(1);// ignore % sign
            size = size/100.f;
            label.size = size;
        }
        else if(s == "font:"){
            label.font = readString(is);
        }
        else{
            std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
            std::cerr << " read in CoordLabel object" << std::endl;
        }
    }
    return label;
}

void MainConfigContainer::loadBorder(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "visibility:"){
                std::string visibilityString = readString(is);
                boardData.border = visibilityString == "Visible";
            }
            else if(s == "thickness:"){
                is >> boardData.borderThickness;
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in Border object" << std::endl;
            }
        }
    }
}

void MainConfigContainer::loadTurnToken(std::istream& is){

    std::string s = readString(is);
    if(s == "["){
        for(s = readString(is); s != "]"; s = readString(is)){
            if(s == "visibility:"){
                std::string visibilityString = readString(is);
                boardData.turnToken = visibilityString == "Visible";
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in TurnToken object" << std::endl;
            }
        }
    }
}