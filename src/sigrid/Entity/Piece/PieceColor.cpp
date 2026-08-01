#include "sigrid/Entity/Piece/PieceColor.h"

#include <iostream>

#include "sigrid/Color/ColorContainer.h"

bool sigrid::PieceColor::load(InputStream& is){

    while(auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "PieceColor: Failed to read string."
                << " Failed to load PieceColor" << std::endl; 
            return false;
        }
        std::string s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "name:"){

            auto name_o = is.readString();
            if(name_o == std::nullopt){

                std::cerr << "PieceColor: Failed to read name."
                    << " Failed to load PieceColor" << std::endl;
                return false;
            }
            std::string name = name_o.value();
        }
        else if(s == "style:"){

            auto styleString_o = is.readString();
            if(styleString_o == std::nullopt){

                std::cerr << "PieceColor: Failed to read style."
                    << " Failed to load PieceColor" << std::endl;
                return false;
            }
            std::string style = styleString_o.value();
            isLight = style == "light";
        }
        else if(s == "lightModifier:"){

            ColorContainer color;
            if(!color.load(is)){

                std::cerr << "PieceColor: Failed to load lightModifier."
                    << " Failed to load PieceColor" << std::endl;
                return false;
            }
            lightModifier = color.value;
        }
        else if(s == "darkModifier:"){

            ColorContainer color;
            if(!color.load(is)){

                std::cerr << "PieceColor: Failed to load darkModifier."
                    << " Failed to load PieceColor" << std::endl;
                return false;
            }
            darkModifier = color.value;
        }
        else{
            std::cerr << "PieceColor: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load PieceColor" << std::endl;
            return false;
        }
    }
    return true;
}