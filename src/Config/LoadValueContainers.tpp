#include "Config/LoadValueContainers.h"

#include <string>
#include <iostream>

#include "Config/IO.h"

template <typename T>
bool sigrid_config::loadValueContainers(sigrid_list::Vector<T>& containers, std::istream& is){

    if(readString(is) != "["){
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){
            std::cerr << "LoadValueContainers: Failed loading string for container"
                << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }

        T container;
        if(!container.setValue(s)){
            return false;
        }
        containers.push_back(std::move(container));
    }
    return true;
}