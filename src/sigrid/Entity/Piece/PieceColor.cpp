#include "sigrid/Entity/Piece/PieceColor.h"

#include <iostream>
#include <sstream>
#include <iomanip>

#include "sigrid/utilities/String/String.h"
#include "sigrid/Color/ColorContainer.h"

bool sigrid::PieceColor::load(InputStream& is){

    while(auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "PieceColor: Failed to read string."
                << " Failed to load PieceColor" << std::endl; 
            return false;
        }
        sigrid::String s = string_o.value();

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
            this->name = name_o.value();
        }
        else if(s == "style:"){

            auto styleString_o = is.readString();
            if(styleString_o == std::nullopt){

                std::cerr << "PieceColor: Failed to read style."
                    << " Failed to load PieceColor" << std::endl;
                return false;
            }
            sigrid::String style = styleString_o.value();
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

sigrid::String sigrid::PieceColor::getString(const int& indentLevel) const{

    sigrid::String styleString;
    if(this->isLight){
        styleString = "light";
    }
    else{
        styleString = "dark";
    }

    sigrid::String lightModifierString;
    {
        std::stringstream ss;
        ss << std::hex << std::setw(6) << std::setfill('0') << this->lightModifier;
        lightModifierString.set(std::move(ss.str()));
    }

    sigrid::String darkModifierString;
    {
        std::stringstream ss;
        ss << std::hex << std::setw(6) << std::setfill('0') << this->darkModifier;
        darkModifierString.set(std::move(ss.str()));
    }

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String out;
    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("name: ");
    out.append(this->name);

    out.append("\n");
    out.append(indent1);
    out.append("style: ");
    out.append(styleString);

    out.append("\n");
    out.append(indent1);
    out.append("lightModifier: ");
    out.append(lightModifierString);

    out.append("\n");
    out.append(indent1);
    out.append("darkModifier: ");
    out.append(darkModifierString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}