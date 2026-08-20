#include "sigrid/Entity/Shape/Arrow/ArrowDataContainer.h"

#include <iostream>

bool sigrid::ArrowDataContainer::load(sigrid::InputStream& is){

    auto colorId_o = is.readInt();
    if(colorId_o == std::nullopt){

        std::cerr << "ArrowDataContainer: Failed to read colorId."
            << " Failed to load ArrowDataContainer." << std::endl;
        return false;
    }
    colorId = colorId_o.value();

    auto positionString_o = is.readString();
    if(positionString_o == std::nullopt){

        std::cerr << "ArrowDataContainer: Failed to read position string."
            << " Failed to load ArrowDataContainer." << std::endl;
        return false;
    }
    position = positionString_o.value();

    return true;
}

sigrid::String sigrid::ArrowDataContainer::getString() const{

    sigrid::String colorIdString;
    colorIdString.set(std::to_string(this->colorId));

    sigrid::String out;
    out.append(colorIdString);
    out.append(" ");
    out.append(this->position);

    return out;
}