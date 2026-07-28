#include "ToolPicker/ToolPickerContainer.h"

#include <iostream>

#include "Config/IO.h"
#include "Config/loadStrings.h"
#include "Config/LoadValues.h"
#include "Config/LoadContainers.h"

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

            if(!sigrid_config::loadContainers<ToolBlockContainer>(pieceBlocks, is)){
                return false;
            }
        }
        else if(s == "MiscTools:"){

            if(!sigrid_config::loadStrings(toolNames, is)){
                return false;
            }
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

            if(!(sigrid_config::loadValues<int>(colorToolIds ,is))){
                return false;
            }
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

            if(!(sigrid_config::loadValues<int>(tileColorIds, is))){
                return false;
            }
        }
        else{
            std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load ToolPicker" << std::endl;
            return false;
        }
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