#include "sigrid/Config/LoadContainers.h"

#include <string>
#include <iostream>

#include "sigrid/Config/IO.h"

template <typename T>
bool sigrid_config::loadContainers(sigrid_list::Vector<T>& containers, std::istream& is){

    if(readString(is) != "["){

        std::cerr << "loadContainers: Failed to load initial \"[\"."
            << " Failed to load Containers" << std::endl;
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "loadContainers: Failed to load string."
                << " Failed to load Containers" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "["){
            T container;
            if(!container.load(is)){

                std::cerr << "loadContainers: Failed to load container."
                    << " Failed to load Containers" << std::endl;
                return false;
            }
            containers.push_back(std::move(container));
        }
    }
    return true;
}