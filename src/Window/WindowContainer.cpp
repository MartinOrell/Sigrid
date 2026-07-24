#include "WindowContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::WindowContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();
        
        if(s == "]"){
            break;
        }
        else if (s == "width:"){

            const auto width_o = sigrid_config::readInt(is);
            if(width_o == std::nullopt){
                return false;
            }
            width = width_o.value();
        }
        else if(s == "height:"){

            const auto height_o = sigrid_config::readInt(is);
            if(height_o == std::nullopt){
                return false;
            }
            height = height_o.value();
        }
        else if(s == "name:"){

            const auto name_o = sigrid_config::readString(is);
            if(name_o == std::nullopt){
                return false;
            }
            name = name_o.value();
        }
        else{
            std::cerr << "WindowContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load Window" << std::endl;
            return false;
        }
    }
    return true;
}