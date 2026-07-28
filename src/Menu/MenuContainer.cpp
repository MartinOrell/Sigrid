#include "MenuContainer.h"

#include <iostream>

#include "Config/IO.h"
#include "Config/LoadNamedContainers.h"

bool sigrid::MenuContainer::load(std::istream& is){

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
        else if(s == "pin:"){

            const auto isPinned_o = sigrid_config::readToggle(is);
            if(isPinned_o == std::nullopt){
                return false;
            }
            isPinned = isPinned_o.value();
            showItems = isPinned;
        }
        else if(s == "font:"){

            const auto fontName_o = sigrid_config::readString(is);
            if(fontName_o == std::nullopt){
                return false;
            }
            fontName = fontName_o.value();
        }
        else if(s == "title:"){

            const auto title_o = sigrid_config::readString(is);
            if(title_o == std::nullopt){
                return false;
            }
            title = title_o.value();
        }
        else if(s == "headers:"){

        if(!(sigrid_config::loadNamedContainers<HeaderContainer>(headers, is))){
                return false;
            }
        }
        else{
            std::cerr << "MenuContainer: Unknown key: \"" << s << "\"";
            std::cerr << " read in Menu object" << std::endl;
            return false;
        }
    }
    return true;
}