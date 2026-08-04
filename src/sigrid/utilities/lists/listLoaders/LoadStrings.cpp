#include "sigrid/utilities/lists/listLoaders/LoadStrings.h"

#include <string>
#include <iostream>

bool sigrid::loadStrings(sigrid_list::Vector<sigrid::String>& strings, sigrid::InputStream& is){

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
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }

        strings.push_back(std::move(s));
    }
    return true;
}