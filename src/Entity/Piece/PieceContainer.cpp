#include "Entity/Piece/PieceContainer.h"

#include <iostream>

#include "Config/IO.h"

using namespace sigrid;

bool PieceContainer::load(std::istream& is){

    for(std::string s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
        if(s == "notation:"){
            name = sigrid_config::readString(is);
        }
        else if(s == "style:"){
            style = sigrid_config::readString(is);
        }
        else if(s == "imageFilename:"){
            filename = sigrid_config::readString(is);
        }
        else{
            std::cerr << "PieceContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed loading PieceContainer" << std::endl;
            return false;
        }
    }

    return true;
}