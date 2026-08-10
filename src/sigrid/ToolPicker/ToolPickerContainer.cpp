#include "sigrid/ToolPicker/ToolPickerContainer.h"

#include <iostream>

#include "sigrid/utilities/lists/listLoaders/LoadStrings.h"
#include "sigrid/utilities/lists/listLoaders/LoadValues.h"
#include "sigrid/utilities/lists/listLoaders/LoadContainers.h"
#include "sigrid/utilities/lists/listSavers/ListSaver.h"

bool sigrid::ToolPickerContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "ToolPickerContainer: Failed to read initial \"[\"."
            << " Failed to load ToolPickerContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "ToolPickerContainer: Failed to read string"
                << " Failed to load ToolPickerContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = is.readVisibility();
            if(isVisible_o == std::nullopt){

                std::cerr << "ToolPickerContainer: Failed to read visibility."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
            show = isVisible_o.value();
        }
        else if(s == "columns:"){

            const auto columns_o = is.readInt();
            if(columns_o == std::nullopt){

                std::cerr << "ToolPickerContainer: Failed to read int for columns."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
            columns = columns_o.value();
        }
        else if(s == "rows:"){

            const auto rows_o = is.readInt();
            if(rows_o == std::nullopt){

                std::cerr << "ToolPickerContainer: Failed to read int for rows."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
            rows = rows_o.value();
        }
        else if(s == "MiscBlock:"){

            if(!miscToolBlock.load(is)){

                std::cerr << "ToolPickerContainer: Failed to load MiscBlock."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            };
        }
        else if(s == "ColorBlock:"){

            if(!colorBlock.load(is)){

                std::cerr << "ToolPickerContainer: Failed to load ColorBlock."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
        }
        else if(s == "PieceBlocks:"){

            if(!sigrid::loadContainers<ToolBlockContainer>(pieceBlocks, is)){

                std::cerr << "ToolPickerContainer: Failed to load PieceBlocks."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
        }
        else if(s == "MiscTools:"){

            if(!sigrid::loadStrings(toolNames, is)){

                std::cerr << "ToolPickerContainer: Failed to load strings for toolnames."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
        }
        else if(s == "defaultArrowColor:"){

            const auto defaultArrowColorId_o = is.readInt();
            if(defaultArrowColorId_o == std::nullopt){

                std::cerr << "ToolPickerContainer: Failed to read int for defaultArrowColor."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
            defaultArrowColorId = defaultArrowColorId_o.value();
        }
        else if(s == "defaultCircleColor:"){

            const auto defaultCircleColorId_o = is.readInt();
            if(defaultCircleColorId_o == std::nullopt){

                std::cerr << "ToolPickerContainer: Failed to read int for defaultCircleColor."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
            defaultCircleColorId = defaultCircleColorId_o.value();
        }
        else if(s == "Colors:"){

            if(!(sigrid::loadValues<int>(colorToolIds, is))){

                std::cerr << "ToolPickerContainer: Failed to load colors"
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
        }
        else if(s == "defaultPiece:"){

            const auto defaultPieceNotation_o = is.readString();
            if(defaultPieceNotation_o == std::nullopt){

                std::cerr << "ToolPickerContainer: Failed to read defaultPiece."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
            defaultPieceNotation = defaultPieceNotation_o.value();
        }
        else if(s == "Pieces:"){

            if(!sigrid::loadStrings(pieceNotations, is)){

                std::cerr << "ToolPickerContainer: Failed to load pieces."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
        }
        else if(s == "TileColors:"){

            if(!(sigrid::loadValues<int>(tileColorIds, is))){

                std::cerr << "ToolPickerContainer: Failed to load TileColors."
                    << " Failed to load ToolPickerContainer" << std::endl;
                return false;
            }
        }
        else{
            std::cerr << "ToolPickerContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load ToolPickerContainer" << std::endl;
            return false;
        }
    }
    return true;
}

std::ostream& sigrid::operator<<(std::ostream& out, const ToolPickerContainer& toolPickerContainer){

    std::string visibilityString;
    if(toolPickerContainer.show){
        visibilityString = "Visible";
    }
    else{
        visibilityString = "Hidden";
    }

    out << "["
        << "\n  visibility: " << visibilityString
        << "\n  columns: " << toolPickerContainer.columns
        << "\n  rows: " << toolPickerContainer.rows
        << "\n  MiscBlock: " << toolPickerContainer.miscToolBlock
        << "\n  ColorBlock: " << toolPickerContainer.colorBlock
        << "\n  PieceBlocks: " << sigrid::ListSaver(toolPickerContainer.pieceBlocks, 1)
        << "\n  MiscTools: " << sigrid::ListSaver(toolPickerContainer.toolNames, 1)
        << "\n  defaultArrowColor: " << toolPickerContainer.defaultArrowColorId
        << "\n  defaultCircleColor: " << toolPickerContainer.defaultCircleColorId
        << "\n  Colors: " << sigrid::ListSaver(toolPickerContainer.colorToolIds, 1)
        << "\n  defaultPiece: " << toolPickerContainer.defaultPieceNotation
        << "\n  Pieces: " << sigrid::ListSaver(toolPickerContainer.pieceNotations, 1)
        << "\n  TileColors: []"
        << "\n]";

    return out;
}