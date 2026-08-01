#include "sigrid/Config/LoadStrings.h"

#include <string>
#include <iostream>

bool sigrid_config::loadStrings(sigrid_list::Vector<std::string>& strings, sigrid::InputStream& is){

    if(is.readString() != "["){

        std::cerr << "loadStrings: Failed to load initial \"[\"."
            << " Failed to load strings" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){
            std::cerr << "loadStrings: Failed to load string."
                << " Failed to load strings" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }

        strings.push_back(std::move(s));
    }
    return true;
}