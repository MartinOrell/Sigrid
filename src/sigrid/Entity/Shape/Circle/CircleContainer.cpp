#include "sigrid/Entity/Shape/Circle/CircleContainer.h"

#include <iostream>

#include "sigrid/Config/IO.h"

bool sigrid::CircleContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){

        std::cerr << "CircleContainer: Failed to read initial \"[\"."
            << " Failed to load CircleContainer" << std::endl;
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "CircleContainer: Failed to read string."
                << " Failed to load CircleContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "diameter:"){

            const auto diameter_o = sigrid_config::readFloat(is);
            if(diameter_o == std::nullopt){

                std::cerr << "CircleContainer: Failed to read float for diameter."
                    << " Failed to load CircleContainer" << std::endl;
                return false;
            }
            diameter = diameter_o.value();
        }
        else{
            std::cerr << "CircleContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load CircleContainer" << std::endl;
            return false;
        }
    }
    return true;
}