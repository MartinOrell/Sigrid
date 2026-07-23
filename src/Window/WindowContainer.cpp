#include "WindowContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::WindowContainer::load(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if (s == "width:"){
                is >> width;
            }
            else if(s == "height:"){
                is >> height;
            }
            else if(s == "name:"){
                is >> name;
            }
            else{
                std::cerr << "WindowContainer: Unknown key: \"" << s << "\"";
                std::cerr << ". Failed to load Window" << std::endl;
                return false;
            }
        }
    }
    return true;
}