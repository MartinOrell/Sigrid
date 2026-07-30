#include "BoardLabelContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::BoardLabelContainer::load(std::istream& is){

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "BoardLabelContainer: Failed to read string."
                << " Failed to load BoardLabelContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "location:"){

            if(!loadLocation(is)){

                std::cerr << "BoardLabelContainer: Failed to load location."
                    << " Failed to load BoardLavelContainer" << std::endl;
                return false;
            }
        }
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read visibility."
                    << "Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "size:"){

            const auto size_o = sigrid_config::readPercentage(is);
            if(size_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read percentage for size."
                    << "Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            size = size_o.value();
        }
        else if(s == "font:"){

            const auto font_o = sigrid_config::readString(is);
            if(font_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read font."
                    << " Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            font = font_o.value();
        }
        else{
            std::cerr << "BoardLabelContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load BoardLabelContainer" << std::endl;
            return false;
        }
    }
    return true;
}

// Location can be "outside/inside left/right/top/bottom"
// Example: "outside left"
bool sigrid::BoardLabelContainer::loadLocation(std::istream& is){

    const auto location_o = sigrid_config::readString(is);
    if(location_o == std::nullopt){

        std::cerr << "BoardLabelContainer::loadLocation: Failed to read string."
            << " Failed to load location for BoardLabelContainer" << std::endl;
        return false;
    }
    const std::string& location = location_o.value();

    isInside = location.substr(0,6) == "inside";
    
    auto spacePos = location.find(' ');
    if(spacePos == std::string::npos){

        std::cerr << "BoardLabelContainer::loadLocation: Failed to find spacebar"
            << " Failed to load location for BoardLabelContainer" << std::endl;
        return false;
    }
    
    std::string orientationString = location.substr(spacePos+1);

    if(orientationString == "left"){
        orientation = sigrid_coord::Orientation::LEFT;
    }
    else if(orientationString == "right"){
        orientation = sigrid_coord::Orientation::RIGHT;
    }
    else if(orientationString == "top"){
        orientation = sigrid_coord::Orientation::TOP;
    }
    else if(orientationString == "bottom"){
        orientation = sigrid_coord::Orientation::BOTTOM;
    }
    else{
        std::cerr << "BoardLabelContainer::loadLocation: Unknown label orientation: \""
            << orientationString << "\"."
            << " Failed to load location for BoardLabelContainer" << std::endl;
        return false;
    }
    return true;
}