#include "ToolContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::ToolContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){

        std::cerr << "ToolContainer: Failed to read initial \"[\"."
            << " Failed to load ToolContainer" << std::endl;
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "ToolContainer: Failed to read string."
                << " Failed to load ToolContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "selection:"){

            const auto selection_o = sigrid_config::readString(is);
            if(selection_o == std::nullopt){

                std::cerr << "ToolContainer: Failed to read string for selection."
                    << " Failed to load ToolContainer" << std::endl;
                return false;
            }
            selection = selection_o.value();
        }
        else if(s == "color:"){

            const auto colorId_o = sigrid_config::readInt(is);
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