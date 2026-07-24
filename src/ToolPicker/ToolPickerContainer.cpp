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

bool sigrid::ToolPickerContainer::loadMiscBlock(std::istream& is){

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
            //Currently not used
        }
        else if(s == "position:"){

            const auto positionString_o = sigrid_config::readString(is);
            if(positionString_o == std::nullopt){
                return false;
            }
            const std::string& position = positionString_o.value();
            miscToolBlock.coord = sigrid_coord::Coord(position);
        }
        else if(s == "columns:"){

            const auto columns_o = sigrid_config::readInt(is);
            if(columns_o == std::nullopt){
                return false;
            }
            miscToolBlock.columns = columns_o.value();
        }
        else if(s == "rows:"){

            const auto rows_o = sigrid_config::readInt(is);
            if(rows_o == std::nullopt){
                return false;
            }
            miscToolBlock.rows = rows_o.value();
        }
        else{
            std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load Misc block" << std::endl;
            return false;
        }
    }
    return true;
}

bool sigrid::ToolPickerContainer::loadColorBlock(std::istream& is){

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
            showColors = isVisible_o.value();
        }
        else if(s == "position:"){

            const auto positionString_o = sigrid_config::readString(is);
            if(positionString_o == std::nullopt){
                return false;
            }
            const std::string& position = positionString_o.value();

            colorBlock.coord = sigrid_coord::Coord(position);
        }
        else if(s == "columns:"){

            const auto columns_o = sigrid_config::readInt(is);
            if(columns_o == std::nullopt){
                return false;
            }
            colorBlock.columns = columns_o.value();
        }
        else if(s == "rows:"){

            const auto rows_o = sigrid_config::readInt(is);
            if(rows_o == std::nullopt){
                return false;
            }
            colorBlock.rows = rows_o.value();
        }
        else{
            std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load ColorBlock" << std::endl;
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

            auto pieceBlock_o = readPieceBlock(is);
            if(pieceBlock_o == std::nullopt){
                return false;
            }
            sigrid_coord::CoordBlock& pieceBlock = pieceBlock_o.value();
            pieceBlocks.push_back(std::move(pieceBlock));
        }
    }
    return true;
}

std::optional<sigrid_coord::CoordBlock> sigrid::ToolPickerContainer::readPieceBlock(std::istream& is){

    sigrid_coord::CoordBlock pieceBlock;
    while(const auto string_o = sigrid_config::readString(is)){

        if(string_o == std::nullopt){
            return std::nullopt;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return std::nullopt;
            }
            //Currently not used
        }
        else if(s == "position:"){

            const auto positionString_o = sigrid_config::readString(is);
            if(positionString_o == std::nullopt){
                return std::nullopt;
            }
            const std::string& position = positionString_o.value();
            pieceBlock.coord = sigrid_coord::Coord{position};
        }
        else if(s == "columns:"){

            const auto columns_o = sigrid_config::readInt(is);
            if(columns_o == std::nullopt){
                return std::nullopt;
            }
            pieceBlock.columns = columns_o.value();
        }
        else if(s == "rows:"){

            const auto rows_o = sigrid_config::readInt(is);
            if(rows_o == std::nullopt){
                return std::nullopt;
            }
            pieceBlock.rows = rows_o.value();
        }
        else{
            std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load PieceBlock" << std::endl;
        }
    }
    return pieceBlock;
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