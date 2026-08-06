#include "sigrid/Entity/Icon/IconDataContainer.h"

#include <iostream>

bool sigrid::IconDataContainer::load(sigrid::InputStream& is){

    auto imageFilename_o = is.readString();
    if(imageFilename_o == std::nullopt){

        std::cerr << "ImageDataContainer: Failed to read imageFilename."
            << " Failed to load IconDataContainer" << std::endl;
        return false;
    }
    this->imageFilename = imageFilename_o.value(); 

    auto positionString_o = is.readString();
    if(positionString_o == std::nullopt){

        std::cerr << "IconDataContainer: Failed to read position string."
            << " Failed to load IconDataContainer" << std::endl;
        return false;
    }
    this->position = positionString_o.value();

    return true;
}

std::ostream& sigrid::operator<<(std::ostream &out, const IconDataContainer &piece)
{
    out << "Icon: " << piece.imageFilename
        << " " << piece.position;

    return out;
}