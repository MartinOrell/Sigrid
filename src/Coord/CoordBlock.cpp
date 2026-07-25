#include "CoordBlock.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid_coord::CoordBlock::load(std::istream& is){

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

            sigrid_coord::Coord newCoord;
            if(!newCoord.load(is)){
                return false;
            }
            coord = std::move(newCoord);
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
        else{
            std::cerr << "CoordBlock: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load CoordBlock" << std::endl;
            return false;
        }
    }
    return true;
}