#include "Config/LoadContainers.h"

#include <string>
#include <iostream>

#include "Config/IO.h"

template <typename T>
bool sigrid_config::loadContainers(sigrid_list::Vector<T>& containers, std::istream& is){

    if(readString(is) != "["){
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){
            std::cerr << "LoadList: Failed loading string for container"
                << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "["){
            T container;
            if(container.load(is)){
                containers.push_back(std::move(container));
            }
            else{
                return false;
            }
        }
    }
    return true;
}