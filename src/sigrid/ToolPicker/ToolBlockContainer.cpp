#include "sigrid/ToolPicker/ToolBlockContainer.h"

#include <iostream>

bool sigrid::ToolBlockContainer::load(InputStream& is){

    while(const auto string_o = is.readString()){

        if(string_o == std::nullopt){

            std::cerr << "ToolBlockContainer: Failed to read string."
                << " Failed to load ToolBlockContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

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