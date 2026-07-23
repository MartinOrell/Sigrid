#include "PieceColor.h"

#include <iostream>

#include "Config/IO.h"
#include "Color/ColorContainer.h"

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
            ColorContainer color;
            color.load(is);
            lightModifier = color.value;
        }
        else if(s == "darkModifier:"){
            ColorContainer color;
            color.load(is);
            darkModifier = color.value;
        }
        else{
            std::cerr << "PieceColor: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load PieceColor" << std::endl;
            return false;
        }
    }
    return true;
}