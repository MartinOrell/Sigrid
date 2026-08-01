#include "sigrid/Entity/Shape/Arrow/ArrowContainer.h"

#include <iostream>

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
        const std::string& s = string_o.value();

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