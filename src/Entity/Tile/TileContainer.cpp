#include "TileContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::TileContainer::load(std::istream& is){

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
        else if(s == "width:"){

            const auto tileWidth_o = sigrid_config::readFloat(is);
            if(tileWidth_o == std::nullopt){
                return false;
            }
            width = tileWidth_o.value();
        }
        else if(s == "height:"){

            const auto tileHeight_o = sigrid_config::readFloat(is);
            if(tileHeight_o == std::nullopt){
                return false;
            }
            height = tileHeight_o.value();
        }
        else{
            std::cerr << "TileContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load tile" << std::endl;
            return false;
        }
    }
    return true;
}