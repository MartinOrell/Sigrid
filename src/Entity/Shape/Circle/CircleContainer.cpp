#include "Entity/Shape/Circle/CircleContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::CircleContainer::load(std::istream& is){

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
        else if(s == "diameter:"){

            const auto diameter_o = sigrid_config::readFloat(is);
            if(diameter_o == std::nullopt){
                return false;
            }
            diameter = diameter_o.value();
        }
        else{
            std::cerr << "CircleContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load circle" << std::endl;
            return false;
        }
    }
    return true;
}