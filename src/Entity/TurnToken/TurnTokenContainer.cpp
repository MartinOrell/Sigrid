#include "Entity/TurnToken/TurnTokenContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::TurnTokenContainer::load(std::istream& is){

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
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else{
            std::cerr << "TurnTokenContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load turn token" << std::endl;
            return false;
        }
    }
    return true;
}