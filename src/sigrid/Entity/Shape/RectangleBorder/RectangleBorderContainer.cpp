#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorderContainer.h"

#include <iostream>

#include "sigrid/Config/IO.h"

bool sigrid::RectangleBorderContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){

        std::cerr << "RectangleBorderContainer: Failed to read initial \"[\"."
            << " Failed to load RectangleBorderContainer" << std::endl;
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "RectangleBorderContainer: Failed to read string."
                << " Failed to load RectangleBorderContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){

                std::cerr << "RectangleBorderContainer: Failed to read visibility."
                    << " Failed to load RectangleBorderContainer" << std::endl;
                return false;
            }
            isVisible = isVisible_o.value();
        }
        else if(s == "thickness:"){

            const auto thickness_o = sigrid_config::readFloat(is);
            if(thickness_o == std::nullopt){

                std::cerr << "RectangleBorderContainer: Failed to read thickness."
                    << " Failed to load RectangleBorderContainer" << std::endl;
                return false;
            }
            thickness = thickness_o.value();
        }
        else{
            std::cerr << "RectangleBorderContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load RectangleBorderContainer" << std::endl;
            return false;
        }
    }
    return true;
}