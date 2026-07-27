#include "Entity/Shape/Arrow/ArrowContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::ArrowContainer::load(std::istream& is){

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
        else if(s == "thickness:"){

            const auto thickness_o = sigrid_config::readFloat(is);
            if(thickness_o == std::nullopt){
                return false;
            }
            thickness = thickness_o.value();
        }
        else if(s == "headSize:"){

            const auto headSize_o = sigrid_config::readFloat(is);
            if(headSize_o == std::nullopt){
                return false;
            }
            headSize = headSize_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load arrow" << std::endl;
            return false;
        }
    }
    return true;
}