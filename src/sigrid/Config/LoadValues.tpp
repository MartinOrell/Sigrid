#include "sigrid/Config/LoadValues.h"

#include <string>
#include <iostream>

#include "sigrid/Config/IO.h"

template <typename T>
bool sigrid_config::loadValues(sigrid_list::Vector<T>& values, sigrid::InputStream& is){

    if(is.readString() != "["){

        std::cerr << "loadValues: Failed to read initial \"[\"."
            << " Failed to load values" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "loadValues: Failed to load string."
                << " Failed to load values" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }

        std::optional<T> value_o = sigrid_config::stringToValue(s);
        if(value_o == std::nullopt){

            std::cerr << "loadValues: Failed to set value from string \""
                << s << "\"."
                << " Failed to load values" << std::endl;
            return false;
        }
        values.push_back(std::move(value_o.value()));
    }
    return true;
}