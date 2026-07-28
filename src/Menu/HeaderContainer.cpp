#include "Menu/HeaderContainer.h"

#include "Config/IO.h"

bool sigrid::HeaderContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }

        MenuItemContainer item;
        item.name = s;
        if(!item.load(is)){
            return false;
        }
        items.push_back(std::move(item));
    }
    return true;
}