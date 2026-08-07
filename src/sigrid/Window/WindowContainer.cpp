#include "sigrid/Window/WindowContainer.h"

#include <iostream>

bool sigrid::WindowContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "WindowContainer: Failed to read initial \"[\"."
            << " Failed to load WindowContainer" << std::endl;
        return false;
    }

    while(auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "WindowContainer: Failed to read string."
                << " Failed to load WindowContainer" << std::endl;
            return false;
        }
        sigrid::String s = string_o.value();
        
        if(s == "]"){
            break;
        }
        else if (s == "width:"){

            const auto width_o = is.readInt();
            if(width_o == std::nullopt){

                std::cerr << "WindowContainer: Failed to read width."
                    << " Failed to load WindowContainer" << std::endl;
                return false;
            }
            width = width_o.value();
        }
        else if(s == "height:"){

            const auto height_o = is.readInt();
            if(height_o == std::nullopt){

                std::cerr << "WindowContainer: Failed to read height."
                    << " Failed to load WindowContainer" << std::endl;
                return false;
            }
            height = height_o.value();
        }
        else if(s == "name:"){

            const auto name_o = is.readString();
            if(name_o == std::nullopt){

                std::cerr << "WindowContainer: Failed to read name."
                    << " Failed to load WindowContainer" << std::endl;
                return false;
            }
            name = name_o.value();
        }
        else{
            std::cerr << "WindowContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load WindowContainer" << std::endl;
            return false;
        }
    }
    return true;
}

std::ostream& sigrid::operator<<(std::ostream& out, const WindowContainer& windowContainer){

    out << "Window: ["
        << "\n  width: " << windowContainer.width
        << "\n  height: " << windowContainer.height
        << "\n  name: "  << windowContainer.name
        << "\n]";

    return out;
}