#include "sigrid/Entity/Shape/Arrow/ArrowContainer.h"

#include <iostream>
#include <sstream>

#include "sigrid/utilities/String/String.h"

bool sigrid::ArrowContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "ArrowContainer: Failed to read initial \"[\"."
            << " Failed to load ArrowContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "ArrowContainer: Failed to read string."
                << " Failed to load ArrowContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "thickness:"){

            const auto thickness_o = is.readFloat();
            if(thickness_o == std::nullopt){

                std::cerr << "ArrowContainer: Failed to read float for thickness."
                    << " Failed to load ArrowContainer" << std::endl;
                return false;
            }
            thickness = thickness_o.value();
        }
        else if(s == "headSize:"){

            const auto headSize_o = is.readFloat();
            if(headSize_o == std::nullopt){

                std::cerr << "ArrowContainer: Failed to read float for headSize."
                    << " Failed to load ArrowContainer" << std::endl;
                return false;
            }
            headSize = headSize_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load ArrowContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::ArrowContainer::getString(const int& indentLevel) const{

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String thicknessString;
    {
        std::ostringstream ss;
        ss << this->thickness;
        thicknessString.set(std::move(ss.str()));
    }

    sigrid::String headSizeString;
    {
        std::ostringstream ss;
        ss << this->headSize;
        headSizeString.set(std::move(ss.str()));
    }

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("thickness: ");
    out.append(thicknessString);

    out.append("\n");
    out.append(indent1);
    out.append("headSize: ");
    out.append(headSizeString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}