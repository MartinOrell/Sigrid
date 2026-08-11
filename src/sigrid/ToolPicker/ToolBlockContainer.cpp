#include "sigrid/ToolPicker/ToolBlockContainer.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"

bool sigrid::ToolBlockContainer::load(InputStream& is){

    while(const auto string_o = is.readString()){

        if(string_o == std::nullopt){

            std::cerr << "ToolBlockContainer: Failed to read string."
                << " Failed to load ToolBlockContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "["){
            continue;
        }
        else if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = is.readVisibility();
            if(isVisible_o == std::nullopt){
                
                std::cerr << "ToolBlockContainer: Failed to read visibility."
                    << " Failed to load ToolBlockContainer" << std::endl;
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "position:"){

            sigrid_coord::Coord coord;
            if(!coord.load(is)){

                std::cerr << "ToolBlockContainer: Failed to load position."
                    << " Failed to load ToolBlockContainer" << std::endl;
                return false;
            }
            block.coord = std::move(coord);
        }
        else if(s == "columns:"){

            const auto columns_o = is.readInt();
            if(columns_o == std::nullopt){

                std::cerr << "ToolBlockContainer: Failed to read int for columns."
                    << " Failed to load ToolBlockContainer" << std::endl;
                return false;
            }
            block.columns = columns_o.value();
        }
        else if(s == "rows:"){

            const auto rows_o = is.readInt();
            if(rows_o == std::nullopt){

                std::cerr << "ToolBlockContainer: Failed to read int for rows."
                    << " Failed to load ToolBlockContainer" << std::endl;
                return false;
            }
            block.rows = rows_o.value();
        }
        else{
            std::cerr << "ToolBlockContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load ToolBlockContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::ToolBlockContainer::getString(const int& indentLevel) const{

    sigrid::String visibilityString;
    if (this->isVisible){
        visibilityString = "Visible";
    }
    else{
        visibilityString = "Hidden";
    }

    sigrid::String columnsString;
    columnsString.set(std::to_string(this->block.columns));
    
    sigrid::String rowsString;
    rowsString.set(std::to_string(this->block.rows));

    sigrid::String indent0 = "";
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("visibility: ");
    out.append(visibilityString);

    out.append("\n");
    out.append(indent1);
    out.append("position: ");
    out.append(this->block.coord.getNotation());

    out.append("\n");
    out.append(indent1);
    out.append("columns: ");
    out.append(columnsString);

    out.append("\n");
    out.append(indent1);
    out.append("rows: ");
    out.append(rowsString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}