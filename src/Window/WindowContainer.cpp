#include "WindowContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::WindowContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();
        
        if(s == "]"){
            break;
        }
        else if (s == "width:"){
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
    return true;
}