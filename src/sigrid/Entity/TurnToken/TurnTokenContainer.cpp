#include "sigrid/Entity/TurnToken/TurnTokenContainer.h"

#include <iostream>

bool sigrid::TurnTokenContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "TurnTokenContainer: Failed to read initial \"[\"."
            << " Failed to load TurnTokenContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "TurnTokenContainer: Failed to read string."
                << " Failed to load TurnTokenContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = is.readVisibility();
            if(isVisible_o == std::nullopt){

                std::cerr << "TurnTokenContainer: Failed to read visibility."
                    << " Failed to load TurnTokenContainer" << std::endl;
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else{
            std::cerr << "TurnTokenContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load TurnTokenContainer" << std::endl;
            return false;
        }
    }
    return true;
}