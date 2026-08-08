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

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ToolContainer& tool){

    out << "["
        << "\n  selection: " << tool.selection
        << "\n  color: " << tool.colorId
        << "\n]";

    return out;
}