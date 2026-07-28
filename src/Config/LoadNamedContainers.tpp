#include "Config/LoadNamedContainers.h"

#include <string>
#include <iostream>

#include "Config/IO.h"

template <typename T>
bool sigrid_config::loadNamedContainers(sigrid_list::Vector<T>& containers, std::istream& is){

    if(readString(is) != "["){
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){
            std::cerr << "LoadNamedContainers: Failed loading string for container"
                << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        
        T container;
        container.name = s;
        if(!(container.load(is))){
            return false;
        }
        containers.push_back(std::move(container));
    }
    return true;
}