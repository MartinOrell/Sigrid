#include "sigrid/Tool/ToolContainer.h"

#include <iostream>

bool sigrid::ToolContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "ToolContainer: Failed to read initial \"[\"."
            << " Failed to load ToolContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "ToolContainer: Failed to read string."
                << " Failed to load ToolContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "selection:"){

            const auto selection_o = is.readString();
            if(selection_o == std::nullopt){

                std::cerr << "ToolContainer: Failed to read string for selection."
                    << " Failed to load ToolContainer" << std::endl;
                return false;
            }
            selection = selection_o.value();
        }
        else if(s == "color:"){

            const auto colorId_o = is.readInt();
            if(colorId_o == std::nullopt){

                std::cerr << "ToolContainer: Failed read int for color."
                    << " Failed to load ToolContainer" << std::endl;
                return false;
            }
            colorId = colorId_o.value();
        }
        else{
            std::cerr << "ToolContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load toolContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::ToolContainer::getString(const int& indentLevel){

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String colorIdString;
    colorIdString.set(std::to_string(this->colorId));

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("selection: ");
    out.append(this->selection);

    out.append("\n");
    out.append(indent1);
    out.append("color: ");
    out.append(colorIdString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}