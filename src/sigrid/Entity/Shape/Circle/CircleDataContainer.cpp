#include "sigrid/Entity/Shape/Circle/CircleDataContainer.h"

#include <iostream>

bool sigrid::CircleDataContainer::load(sigrid::InputStream& is){

    auto colorId_o = is.readInt();
    if(colorId_o == std::nullopt){

        std::cerr << "CircleDataContainer: Failed to read colorId."
            << " Failed to load CircleDataContainer." << std::endl;
        return false;
    }
    colorId = colorId_o.value();

    auto positionString_o = is.readString();
    if(positionString_o == std::nullopt){

        std::cerr << "CircleDataContainer: Failed to read position string."
            << " Failed to load CircleDataContainer." << std::endl;
        return false;
    }
    position = positionString_o.value();

    return true;
}

sigrid::String sigrid::CircleDataContainer::getString() const{

    sigrid::String colorIdString;
    colorIdString.set(std::to_string(this->colorId));

    sigrid::String out;
    out.append(colorIdString);
    out.append(" ");
    out.append(this->position);

    return out;
}