#include "sigrid/Config/LoadContainers.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"

template <typename T>
bool sigrid_config::loadContainers(sigrid_list::Vector<T>& containers, sigrid::InputStream& is){

    if(is.readString() != "["){

        std::cerr << "loadContainers: Failed to load initial \"[\"."
            << " Failed to load Containers" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "loadContainers: Failed to load string."
                << " Failed to load Containers" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

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