#include "sigrid/Entity/Piece/PieceDataContainer.h"

#include <iostream>

bool sigrid::PieceDataContainer::load(sigrid::InputStream& is){

    auto colorId_o = is.readInt();
    if(colorId_o == std::nullopt){

        std::cerr << "PieceDataContainer: Failed to read colorId."
            << " Failed to load PieceDataContainer" << std::endl;
        return false;
    }
    colorId = colorId_o.value();

    auto name_o = is.readString();
    if(name_o == std::nullopt){

        std::cerr << "PieceDataContainer: Failed to read name."
            << " Failed to load PieceDataContainer" << std::endl;
        return false;
    }
    name = name_o.value(); 

    auto positionString_o = is.readString();
    if(positionString_o == std::nullopt){

        std::cerr << "PieceDataContainer: Failed to read position string."
            << " Failed to load PieceDataContainer" << std::endl;
        return false;
    }
    position = positionString_o.value();

    return true;
}

std::ostream& sigrid::operator<<(std::ostream &out, const PieceDataContainer &piece)
{
    out << "Piece: " << piece.colorId
        << " " << piece.name
        << " " << piece.position;

    return out;
}