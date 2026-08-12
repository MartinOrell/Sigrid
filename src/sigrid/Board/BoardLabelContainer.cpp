#include "sigrid/Board/BoardLabelContainer.h"

#include <iostream>
#include <sstream>

bool sigrid::BoardLabelContainer::load(InputStream& is){

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "BoardLabelContainer: Failed to read string."
                << " Failed to load BoardLabelContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "location:"){

            if(!location.load(is)){

                std::cerr << "BoardLabelContainer: Failed to load location."
                    << " Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
        }
        else if(s == "visibility:"){

            const auto isVisible_o = is.readVisibility();
            if(isVisible_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read visibility."
                    << "Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "size:"){

            const auto size_o = is.readPercentage();
            if(size_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read percentage for size."
                    << "Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            size = size_o.value();
        }
        else if(s == "font:"){

            const auto font_o = is.readString();
            if(font_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read font."
                    << " Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            font = font_o.value();
        }
        else{
            std::cerr << "BoardLabelContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load BoardLabelContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::BoardLabelContainer::getString(const int& indentLevel) const{

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; i++){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String visibilityString;
    if(this->isVisible){
        visibilityString = "Visible";
    }
    else{
        visibilityString = "Hidden";
    }

    sigrid::String sizeString;
    {
        std::ostringstream ss;
        float percentSize = this->size * 100.f;
        ss << percentSize << "%";
        sizeString.set(std::move(ss.str()));
    }

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("location: ");
    out.append(location.getString());

    out.append("\n");
    out.append(indent1);
    out.append("visibility: ");
    out.append(visibilityString);

    out.append("\n");
    out.append(indent1);
    out.append("size: ");
    out.append(sizeString);

    out.append("\n");
    out.append(indent1);
    out.append("font: ");
    out.append(this->font);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}