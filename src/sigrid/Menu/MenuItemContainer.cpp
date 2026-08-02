#include "sigrid/Menu/MenuItemContainer.h"

#include <iostream>

bool sigrid::MenuItemContainer::load(InputStream& is){

    {
        const auto string_o = is.readString();
        if(string_o == std::nullopt){

            std::cerr << "MenuItemContainer: Failed to read initial string."
                << " Failed to load MenuItemContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s != "["){
            displayNames.push_back(name);
            actionNames.push_back(s);
            return true;
        }
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "MenuItemContainer: Failed to read string."
                << " Failed to load MenuItemContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        displayNames.push_back(s);

        const auto actionName_o = is.readString();
        if(actionName_o == std::nullopt){

            std::cerr << "MenuItemContainer: Failed to read string for actionName."
                << " Failed to load MenuItemContainer" << std::endl;
            return false;
        }
        actionNames.push_back(actionName_o.value());
    }
    return true;
}