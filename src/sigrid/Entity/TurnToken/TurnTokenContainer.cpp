#include "sigrid/Entity/TurnToken/TurnTokenContainer.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"

bool sigrid::TurnTokenContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "TurnTokenContainer: Failed to read initial \"[\"."
            << " Failed to load TurnTokenContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "TurnTokenContainer: Failed to read string."
                << " Failed to load TurnTokenContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = is.readVisibility();
            if(isVisible_o == std::nullopt){

                std::cerr << "TurnTokenContainer: Failed to read visibility."
                    << " Failed to load TurnTokenContainer" << std::endl;
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else{
            std::cerr << "TurnTokenContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load TurnTokenContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::TurnTokenContainer::getString(const int& indentLevel) const{

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
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

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("visibility: ");
    out.append(visibilityString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}