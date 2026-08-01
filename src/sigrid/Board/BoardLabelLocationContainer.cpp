#include "sigrid/Board/BoardLabelLocationContainer.h"

#include <iostream>

// Location can be "outside/inside left/right/top/bottom"
// Example: "outside left"
bool sigrid::BoardLabelLocationContainer::load(InputStream& is){

    const auto locationString_o = is.readString();
    if(locationString_o == std::nullopt){

        std::cerr << "BoardLabelLocationContainer: Failed to read string."
            << " Failed to load BoardLabelLocationContainer" << std::endl;
        return false;
    }
    const std::string& locationString = locationString_o.value();

    isInside = locationString.substr(0,6) == "inside";
    
    auto spacePos = locationString.find(' ');
    if(spacePos == std::string::npos){

        std::cerr << "BoardLabelLocationContainer: Failed to find spacebar."
            << " Failed to load BoardLabelLocationContainer" << std::endl;
        return false;
    }
    
    std::string orientationString = locationString.substr(spacePos+1);

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
        std::cerr << "BoardLabelLocationContainer: Unknown label orientation: \""
            << orientationString << "\"."
            << " Failed to load BoardLabelLocationContainer" << std::endl;
        return false;
    }
    return true;
}