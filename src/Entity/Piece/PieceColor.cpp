#include "PieceColor.h"

#include <iostream>

#include "Config/IO.h"
#include "Color/ColorContainer.h"

bool sigrid::PieceColor::load(std::istream& is){

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();
        if(s == "]"){
            break;
        }
        else if(s == "name:"){
            auto name_o = sigrid_config::readString(is);
            if(name_o == std::nullopt){
                return false;
            }
            std::string name = name_o.value();
        }
        else if(s == "style:"){
            auto styleString_o = sigrid_config::readString(is);
            if(styleString_o == std::nullopt){
                return false;
            }
            std::string style = styleString_o.value();
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