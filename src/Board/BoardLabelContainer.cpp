#include "BoardLabelContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::BoardLabelContainer::load(std::istream& is){

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "location:"){

            if(!loadLocation(is)){
                return false;
            }
        }
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "size:"){

            const auto size_o = sigrid_config::readPercentage(is);
            if(size_o == std::nullopt){
                return false;
            }
            size = size_o.value();
        }
        else if(s == "font:"){

            const auto font_o = sigrid_config::readString(is);
            if(font_o == std::nullopt){
                return false;
            }
            font = font_o.value();
        }
        else{
            std::cerr << "BoardLabelContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load coordLabel" << std::endl;
        }
    }
    return true;
}

// Location can be "outside/inside left/right/top/bottom"
// Example: "outside left"
bool sigrid::BoardLabelContainer::loadLocation(std::istream& is){

    const auto location_o = sigrid_config::readString(is);
    if(location_o == std::nullopt){
        return false;
    }
    const std::string& location = location_o.value();

    isInside = location.substr(0,6) == "inside";
    
    auto spacePos = location.find(' ');
    if(spacePos == std::string::npos){
        return false;
    }
    
    std::string orientation = location.substr(spacePos+1);

    if(orientation == "left"){
        position = 0;
    }
    else if(orientation == "right"){
        position = 1;
    }
    else if(orientation == "top"){
        position = 2;
    }
    else if(orientation == "bottom"){
        position = 3;
    }
    else{
        std::cerr << "BoardLabelContainer: Unknown label orientation: " << orientation << std::endl;
        return false;
    }
    return true;
}