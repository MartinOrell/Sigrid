#include "ToolPicker/ToolPickerContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::ToolPickerContainer::load(std::istream& is){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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

            const auto visibilityString_o = sigrid_config::readString(is);
            if(visibilityString_o == std::nullopt){
                return false;
            }
            const std::string& visibilityString = visibilityString_o.value();
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

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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

            const auto visibilityString_o = sigrid_config::readString(is);
            if(visibilityString_o == std::nullopt){
                return false;
            }
            const std::string& visibilityString = visibilityString_o.value();
            bool isVisible = visibilityString == "Visible";
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
    return true;
}

bool sigrid::ToolPickerContainer::loadColorBlock(std::istream& is){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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

            const auto visibilityString_o = sigrid_config::readString(is);
            if(visibilityString_o == std::nullopt){
                return false;
            }
            const std::string& visibilityString = visibilityString_o.value();

            bool isVisible = visibilityString == "Visible";
            showColors = isVisible;
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
    return true;
}

bool sigrid::ToolPickerContainer::loadPieceBlocks(std::istream& is){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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

            const auto visibilityString_o = sigrid_config::readString(is);
            if(visibilityString_o == std::nullopt){
                return std::nullopt;
            }
            const std::string& visibilityString = visibilityString_o.value();

            bool isVisible = visibilityString == "Visible";
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

    {
        auto const string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
        }
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