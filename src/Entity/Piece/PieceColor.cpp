#include "PieceColor.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::PieceColor::load(std::istream& is){

    for(std::string s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
        if(s == "name:"){
            std::string name = sigrid_config::readString(is);
        }
        else if(s == "style:"){
            std::string style = sigrid_config::readString(is);
            isLight = style == "light";
        }
        else if(s == "lightModifier:"){
            lightModifier = sigrid_config::readColor(is);
        }
        else if(s == "darkModifier:"){
            darkModifier = sigrid_config::readColor(is);
        }
        else{
            std::cerr << "PieceColor: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load PieceColor" << std::endl;
            return false;
        }
    }
    return true;
}