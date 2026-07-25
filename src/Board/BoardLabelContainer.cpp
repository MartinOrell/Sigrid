#include "BoardLabelContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::BoardLabelContainer::load(std::istream& is){

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "position:"){

            const auto positionString_o = sigrid_config::readString(is);
            if(positionString_o == std::nullopt){
                return false;
            }
            const std::string& positionString = positionString_o.value();

            isInside = positionString.substr(0,6) == "inside";
            auto spacePos = positionString.find(' ');
            if(spacePos != std::string::npos){
                std::string positionString2 = positionString.substr(spacePos+1);
                if(positionString2 == "left"){
                    position = 0;
                }
                else if(positionString2 == "right"){
                    position = 1;
                }
                else if(positionString2 == "top"){
                    position = 2;
                }
                else if(positionString2 == "bottom"){
                    position = 3;
                }
                else{
                    std::cerr << "BoardDesignContainer: Unknown label position: " << positionString2 << std::endl;
                }
            }
        }
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "size:"){

            const auto size_o = sigrid_config::readPercentage(is);
            if(size_o == std::nullopt){
                return false;
            }
            size = size_o.value();
        }
        else if(s == "font:"){

            const auto font_o = sigrid_config::readString(is);
            if(font_o == std::nullopt){
                return false;
            }
            font = font_o.value();
        }
        else{
            std::cerr << "BoardLabelContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load coordLabel" << std::endl;
        }
    }
    return true;
}