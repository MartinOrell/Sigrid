#include "ToolContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::ToolContainer::load(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "selection:"){
                selection = sigrid_config::readString(is);
            }
            else if(s == "color:"){
                is >> colorId;
            }
            else{
                std::cerr << "ToolContainer: Unknown key: \"" << s << "\"";
                std::cerr << ". Failed to load toolContainer" << std::endl;
                return false;
            }
        }
    }
    return true;
}