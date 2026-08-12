#include "sigrid/Board/BoardLabelLocationContainer.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"

// Location can be "outside/inside left/right/top/bottom"
// Example: "outside left"
bool sigrid::BoardLabelLocationContainer::load(InputStream& is){

    const auto locationString_o = is.readString();
    if(locationString_o == std::nullopt){

        std::cerr << "BoardLabelLocationContainer: Failed to read string."
            << " Failed to load BoardLabelLocationContainer" << std::endl;
        return false;
    }
    const sigrid::String& locationString = locationString_o.value();

    isInside = locationString.substr(0,6) == "inside";
    
    auto spacePos_o = locationString.find(' ');
    if(spacePos_o == std::nullopt){

        std::cerr << "BoardLabelLocationContainer: Failed to find spacebar."
            << " Failed to load BoardLabelLocationContainer" << std::endl;
        return false;
    }
    int spacePos = spacePos_o.value();
    
    auto orientationString_o = locationString.substr(spacePos+1);

    if(orientationString_o == std::nullopt){

        std::cerr << "BoardLabelLocationContainer: Failed to get orientationString from LocationString."
            << " Failed to load BoardLabelLocationContainer" << std::endl;
        return false;
    }
    sigrid::String orientationString = orientationString_o.value();

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

sigrid::String sigrid::BoardLabelLocationContainer::getString() const{

    sigrid::String isInsideString;
    if(this->isInside){
        isInsideString = "inside";
    }
    else{
        isInsideString = "outside";
    }

    sigrid::String orientationString;
    switch(this->orientation){
        case sigrid_coord::Orientation::LEFT:
            orientationString = "left";
            break;
        case sigrid_coord::Orientation::RIGHT:
            orientationString = "right";
            break;
        case sigrid_coord::Orientation::TOP:
            orientationString = "top";
            break;
        case sigrid_coord::Orientation::BOTTOM:
            orientationString = "bottom";
            break;
        default:
            return "[]";
    }

    sigrid::String out;
    out.append("\"");
    out.append(isInsideString);
    out.append(" ");
    out.append(orientationString);
    out.append("\"");

    return out;
}