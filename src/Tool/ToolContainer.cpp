#include "ToolContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::ToolContainer::load(std::istream& is){

    auto string_o = sigrid_config::readString(is);
    if(string_o == std::nullopt){
        return false;
    }
    std::string s = string_o.value();
    if(s == "["){
        while(string_o = sigrid_config::readString(is)){
            
            if(string_o == std::nullopt){
                return false;
            }
            s = string_o.value();
            if(s == "]"){
                break;
            }
            else if(s == "selection:"){
                auto selection_o = sigrid_config::readString(is);
                if(selection_o == std::nullopt){
                    return false;
                }
                selection = selection_o.value();
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