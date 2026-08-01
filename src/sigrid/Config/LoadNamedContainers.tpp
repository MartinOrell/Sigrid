#include "sigrid/Config/LoadNamedContainers.h"

#include <string>
#include <iostream>

template <typename T>
bool sigrid_config::loadNamedContainers(sigrid_list::Vector<T>& containers, sigrid::InputStream& is){

    if(is.readString() != "["){

        std::cerr << "loadNamedContainers: Failed to load initial \"[\"."
            << "Failed to load namedContainers" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "loadNamedContainers: Failed to load string."
                << "Failed to load namedContainers" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        
        T container;
        container.name = s;
        if(!(container.load(is))){

            std::cerr << "loadNamedContainers: Failed to load container."
                << "Failed to load namedContainers" << std::endl;
            return false;
        }
        containers.push_back(std::move(container));
    }
    return true;
}