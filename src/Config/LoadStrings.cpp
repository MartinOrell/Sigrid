#include "Config/LoadStrings.h"

#include <string>
#include <iostream>

#include "Config/IO.h"
#include "LoadStrings.h"

bool sigrid_config::loadStrings(sigrid_list::Vector<std::string>& strings, std::istream& is){

    if(readString(is) != "["){
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){
            std::cerr << "LoadValues: Failed loading string for value"
                << std::endl;
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