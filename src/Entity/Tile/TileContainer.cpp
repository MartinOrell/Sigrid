#include "TileContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::TileContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){

        std::cerr << "TileContainer: Failed to load initial \"[\"."
            << " Failed to load TileContainer" << std::endl;
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "TileContainer: Failed to read string."
                << " Failed to load TileContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "width:"){

            const auto width_o = sigrid_config::readFloat(is);
            if(width_o == std::nullopt){

                std::cerr << "TileContainer: Failed to read float for width."
                    << " Failed to load TileContainer" << std::endl;
                return false;
            }
            width = width_o.value();
        }
        else if(s == "height:"){

            const auto height_o = sigrid_config::readFloat(is);
            if(height_o == std::nullopt){

                std::cerr << "TileContainer: Failed to read float for height."
                    << " Failed to load TileContainer" << std::endl;
                return false;
            }
            height = height_o.value();
        }
        else{
            std::cerr << "TileContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load tileContainer" << std::endl;
            return false;
        }
    }
    return true;
}