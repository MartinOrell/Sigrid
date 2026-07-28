#include "MenuItemContainer.h"

#include "Config/IO.h"

bool sigrid::MenuItemContainer::load(std::istream& is){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            displayNames.push_back(name);
            actionNames.push_back(s);
            return true;
        }
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        displayNames.push_back(s);

        {
            const auto actionName_o = sigrid_config::readString(is);
            if(actionName_o == std::nullopt){
                return false;
            }
            actionNames.push_back(actionName_o.value());
        }
        
        {
            const auto displayName_o = sigrid_config::readString(is);
            if(displayName_o == std::nullopt){
                return false;
            }
            displayNames.push_back(displayName_o.value());
        }
        
        {
            const auto actionName_o = sigrid_config::readString(is);
            if(actionName_o == std::nullopt){
                return false;
            }
            actionNames.push_back(actionName_o.value());
        }
    }
    return true;
}