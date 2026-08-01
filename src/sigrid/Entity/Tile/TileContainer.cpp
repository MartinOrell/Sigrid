#include "sigrid/Entity/Tile/TileContainer.h"

#include <iostream>

bool sigrid::TileContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "TileContainer: Failed to load initial \"[\"."
            << " Failed to load TileContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
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

            const auto width_o = is.readFloat();
            if(width_o == std::nullopt){

                std::cerr << "TileContainer: Failed to read float for width."
                    << " Failed to load TileContainer" << std::endl;
                return false;
            }
            width = width_o.value();
        }
        else if(s == "height:"){

            const auto height_o = is.readFloat();
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