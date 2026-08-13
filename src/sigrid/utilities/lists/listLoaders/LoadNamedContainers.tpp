#include "sigrid/utilities/lists/listLoaders/LoadNamedContainers.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"

template <typename T>
bool sigrid::loadNamedContainers(sigrid_list::Vector<T>& containers, sigrid::InputStream& is){

    if(is.readString() != "["){

        std::cerr << "loadNamedContainers: Failed to load initial \"[\"."
            << " Failed to load namedContainers" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "loadNamedContainers: Failed to load string."
                << " Failed to load namedContainers" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        
        T container;
        container.name = s;
        if(!(container.load(is))){

            std::cerr << "loadNamedContainers<" << typeid(containers).name() << ">"
                << ": Failed to load container named \"" << container.name << "\"."
                << " Failed to load namedContainers" << std::endl;
            return false;
        }
        containers.push_back(std::move(container));
    }
    return true;
}