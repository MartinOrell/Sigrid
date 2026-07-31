#include "BoardLabelContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::BoardLabelContainer::load(std::istream& is){

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "BoardLabelContainer: Failed to read string."
                << " Failed to load BoardLabelContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

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

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read visibility."
                    << "Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "size:"){

            const auto size_o = sigrid_config::readPercentage(is);
            if(size_o == std::nullopt){

                std::cerr << "BoardLabelContainer: Failed to read percentage for size."
                    << "Failed to load BoardLabelContainer" << std::endl;
                return false;
            }
            size = size_o.value();
        }
        else if(s == "font:"){

            const auto font_o = sigrid_config::readString(is);
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