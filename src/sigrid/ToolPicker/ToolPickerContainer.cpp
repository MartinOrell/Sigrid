#include "sigrid/ToolPicker/ToolPickerContainer.h"

#include <iostream>

#include "sigrid/utilities/lists/listLoaders/LoadStrings.h"
#include "sigrid/utilities/lists/listLoaders/LoadValues.h"
#include "sigrid/utilities/lists/listLoaders/LoadContainers.h"
#include "sigrid/utilities/lists/listSavers/ListSaver.h"
#include "sigrid/utilities/lists/listSavers/StringListSaver.h"
#include "sigrid/utilities/lists/listSavers/IntListSaver.h"

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
        else if(s == "PieceBlockColors:"){

            if(!(sigrid::loadValues<int>(pieceBlockColors, is))){

                std::cerr << "ToolPickerContainer: Failed to load PieceBlockColors."
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

sigrid::String sigrid::ToolPickerContainer::getString(const int& indentLevel) const{

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String visibilityString;
    if(this->show){
        visibilityString = "Visible";
    }
    else{
        visibilityString = "Hidden";
    }

    sigrid::String columnsString;
    columnsString.set(std::to_string(this->columns));

    sigrid::String rowsString;
    rowsString.set(std::to_string(this->rows));

    sigrid::String defaultArrowColorIdString;
    defaultArrowColorIdString.set(std::to_string(this->defaultArrowColorId));

    sigrid::String defaultCircleColorIdString;
    defaultCircleColorIdString.set(std::to_string(this->defaultCircleColorId));

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("visibility: ");
    out.append(visibilityString);

    out.append("\n");
    out.append(indent1);
    out.append("columns: ");
    out.append(columnsString);

    out.append("\n");
    out.append(indent1);
    out.append("rows: ");
    out.append(rowsString);

    out.append("\n");
    out.append(indent1);
    out.append("MiscBlock: ");
    out.append(this->miscToolBlock.getString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("ColorBlock: ");
    out.append(this->colorBlock.getString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("PieceBlocks: ");
    out.append(sigrid::ListSaver(this->pieceBlocks).getMultiLineString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("MiscTools: ");
    out.append(sigrid::StringListSaver(this->toolNames).getMultiLineString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("defaultArrowColor: ");
    out.append(defaultArrowColorIdString);

    out.append("\n");
    out.append(indent1);
    out.append("defaultCircleColor: ");
    out.append(defaultCircleColorIdString);

    out.append("\n");
    out.append(indent1);
    out.append("Colors: ");
    out.append(sigrid::IntListSaver(this->colorToolIds).getMultiLineString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("defaultPiece: ");
    out.append(this->defaultPieceNotation);

    out.append("\n");
    out.append(indent1);
    out.append("Pieces: ");
    out.append(sigrid::StringListSaver(this->pieceNotations).getMultiLineString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("TileColors: ");
    out.append(sigrid::IntListSaver(this->tileColorIds).getMultiLineString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("PieceBlockColors: ");
    out.append(sigrid::IntListSaver(this->pieceBlockColors).getMultiLineString(indentLevel+1));

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}