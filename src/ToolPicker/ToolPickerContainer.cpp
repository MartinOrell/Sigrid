#include "ToolPicker/ToolPickerContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::ToolPickerContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return false;
            }
            show = isVisible_o.value();
        }
        else if(s == "columns:"){

            const auto columns_o = sigrid_config::readInt(is);
            if(columns_o == std::nullopt){
                return false;
            }
            columns = columns_o.value();
        }
        else if(s == "rows:"){

            const auto rows_o = sigrid_config::readInt(is);
            if(rows_o == std::nullopt){
                return false;
            }
            rows = rows_o.value();
        }
        else if(s == "MiscBlock:"){

            if(!miscToolBlock.load(is)){
                return false;
            };
        }
        else if(s == "ColorBlock:"){

            if(!colorBlock.load(is)){
                return false;
            }
        }
        else if(s == "PieceBlocks:"){

            if(!loadPieceBlocks(is)){
                return false;
            }
        }
        else if(s == "MiscTools:"){
            loadMiscTools(is);
        }
        else if(s == "defaultArrowColor:"){

            const auto defaultArrowColorId_o = sigrid_config::readInt(is);
            if(defaultArrowColorId_o == std::nullopt){
                return false;
            }
            defaultArrowColorId = defaultArrowColorId_o.value();
        }
        else if(s == "defaultCircleColor:"){

            const auto defaultCircleColorId_o = sigrid_config::readInt(is);
            if(defaultCircleColorId_o == std::nullopt){
                return false;
            }
            defaultCircleColorId = defaultCircleColorId_o.value();
        }
        else if(s == "Colors:"){
            loadToolColors(is);
        }
        else if(s == "defaultPiece:"){

            const auto defaultPieceNotation_o = sigrid_config::readString(is);
            if(defaultPieceNotation_o == std::nullopt){
                return false;
            }
            defaultPieceNotation = defaultPieceNotation_o.value();
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
    return true;
}

bool sigrid::ToolPickerContainer::loadPieceBlocks(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }
    
    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "["){

            sigrid_coord::CoordBlock pieceBlock;
            if(!pieceBlock.load(is)){
                return false;
            }
            pieceBlocks.push_back(std::move(pieceBlock));
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadMiscTools(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        toolNames.push_back(s);
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadToolColors(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        int colorId = std::stoi(s);
        colorToolIds.push_back(colorId);
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadToolPieces(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        pieceNotations.push_back(s);
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadToolPickerTileColors(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        int colorId = std::stoi(s);
        tileColorIds.push_back(colorId);
    }
    return true;
}