#include "sigrid/Config/LoadValueContainers.h"

#include <string>
#include <iostream>

#include "sigrid/Config/IO.h"

template <typename T>
bool sigrid_config::loadValueContainers(sigrid_list::Vector<T>& containers, std::istream& is){

    if(readString(is) != "["){

        std::cerr << "loadValueContainers: Failed to load initial \"[\"."
            << " Failed to load valueContainers" << std::endl; 
        return false;
    }

    while(const auto string_o = readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "loadValueContainers: Failed to load string."
                << " Failed to load valueContainers" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }

        T container;
        if(!container.setValue(s)){

            std::cerr << "loadValueContainers: Failed to set value from string \""
                << s << "\"."
                << " Failed to load valueContainers" << std::endl;
            return false;
        }
        containers.push_back(std::move(container));
    }
    return true;
}