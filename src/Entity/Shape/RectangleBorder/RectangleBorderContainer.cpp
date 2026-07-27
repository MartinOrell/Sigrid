#include "Entity/Shape/RectangleBorder/RectangleBorderContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::RectangleBorderContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "thickness:"){

            const auto thickness_o = sigrid_config::readFloat(is);
            if(thickness_o == std::nullopt){
                return false;
            }
            thickness = thickness_o.value();
        }
        else{
            std::cerr << "RectangleBorderContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load border" << std::endl;
            return false;
        }
    }
    return true;
}