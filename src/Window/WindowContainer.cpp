#include "WindowContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::WindowContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){

        std::cerr << "WindowContainer: Failed reading first \"[\"."
            << " Failed to load WindowContainer" << std::endl;
        return false;
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            
            std::cerr << "WindowContainer: Failed reading string."
                << " Failed to load WindowContainer" << std::endl;
            return false;
        }
        std::string s = string_o.value();
        
        if(s == "]"){
            break;
        }
        else if (s == "width:"){

            const auto width_o = sigrid_config::readInt(is);
            if(width_o == std::nullopt){

                std::cerr << "WindowContainer: Failed reading width."
                    << " Failed to load WindowContainer" << std::endl;
                return false;
            }
            width = width_o.value();
        }
        else if(s == "height:"){

            const auto height_o = sigrid_config::readInt(is);
            if(height_o == std::nullopt){

                std::cerr << "WindowContainer: Failed reading height."
                    << " Failed to load WindowContainer" << std::endl;
                return false;
            }
            height = height_o.value();
        }
        else if(s == "name:"){

            const auto name_o = sigrid_config::readString(is);
            if(name_o == std::nullopt){

                std::cerr << "WindowContainer: Failed reading name."
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