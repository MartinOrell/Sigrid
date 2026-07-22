#include "ToolPicker/ToolPickerContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::ToolPickerContainer::load(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "visibility:"){
                std::string visibilityString = sigrid_config::readString(is);
                bool isVisible = visibilityString == "Visible";
                show = isVisible;
            }
            else if(s == "columns:"){
                is >> columns;
            }
            else if(s == "rows:"){
                is >> rows;
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
            else if(s == "defaultArrowColor:"){
                is >> defaultArrowColorId;
            }
            else if(s == "defaultCircleColor:"){
                is >> defaultCircleColorId;
            }
            else if(s == "Colors:"){
                loadToolColors(is);
            }
            else if(s == "defaultPiece:"){
                defaultPieceNotation = sigrid_config::readString(is);
            }
            else if(s == "Pieces:"){
                loadToolPieces(is);
            }
            else if(s == "TileColors:"){
                loadToolPickerTileColors(is);
            }
            else{
                std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
                std::cerr << ". Failed to load ToolPicker" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadMiscBlock(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){

            if(s == "visibility:"){
                std::string visibilityString = sigrid_config::readString(is);
                bool isVisible = visibilityString == "Visible";
                //Currently not used
            }
            else if(s == "position:"){
                std::string position = sigrid_config::readString(is);
                miscToolBlock.coord = sigrid_coord::Coord(position);
            }
            else if(s == "columns:"){
                is >> miscToolBlock.columns;
            }
            else if(s == "rows:"){
                is >> miscToolBlock.rows;
            }
            else{
                std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
                std::cerr << ". Failed to load Misc block" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadColorBlock(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){

            if(s == "visibility:"){
                std::string visibilityString = sigrid_config::readString(is);
                bool isVisible = visibilityString == "Visible";
                showColors = isVisible;
            }
            else if(s == "position:"){
                std::string position = sigrid_config::readString(is);
                colorBlock.coord = sigrid_coord::Coord(position);
            }
            else if(s == "columns:"){
                is >> colorBlock.columns;
            }
            else if(s == "rows:"){
                is >> colorBlock.rows;
            }
            else{
                std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
                std::cerr << ". Failed to load ColorBlock" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadPieceBlocks(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "["){
                sigrid_coord::CoordBlock pieceBlock = readPieceBlock(is);
                pieceBlocks.push_back(pieceBlock);
            }
        }
    }
    return true;
}

sigrid_coord::CoordBlock sigrid::ToolPickerContainer::readPieceBlock(std::istream& is){

    sigrid_coord::CoordBlock pieceBlock;
    for(std::string s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){

        if(s == "visibility:"){
            std::string visibilityString = sigrid_config::readString(is);
            bool isVisible = visibilityString == "Visible";
            //Currently not used
        }
        else if(s == "position:"){
            std::string position = sigrid_config::readString(is);
            pieceBlock.coord = sigrid_coord::Coord{position};
        }
        else if(s == "columns:"){
            is >> pieceBlock.columns;
        }
        else if(s == "rows:"){
            is >> pieceBlock.rows;
        }
        else{
            std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load PieceBlock" << std::endl;
        }
    }
    return pieceBlock;
}

bool sigrid::ToolPickerContainer::loadMiscTools(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            toolNames.push_back(s);
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadToolColors(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            int colorId = std::stoi(s);
            colorToolIds.push_back(colorId);
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadToolPieces(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            pieceNotations.push_back(s);
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadToolPickerTileColors(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            int colorId = std::stoi(s);
            tileColorIds.push_back(colorId);
        }
    }
    return true;
}