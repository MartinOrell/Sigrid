#include "Config/LoadValues.h"

#include <string>
#include <iostream>

#include "Config/IO.h"

template <typename T>
bool sigrid_config::loadValues(sigrid_list::Vector<T>& values, std::istream& is){

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

        std::optional<T> value_o = sigrid_config::stringToValue(s);
        if(value_o == std::nullopt){
            return false;
        }
        values.push_back(std::move(value_o.value()));
    }
    return true;
}