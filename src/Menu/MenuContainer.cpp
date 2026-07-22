#include "MenuContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::MenuContainer::load(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "pin:"){
                isPinned = sigrid_config::readToggle(is);
                showItems = isPinned;
            }
            else if(s == "font:"){
                fontName = sigrid_config::readString(is);
            }
            else if(s == "title:"){
                title = sigrid_config::readString(is);
            }
            else if(s == "headers:"){
                loadHeaders(is);
            }
            else{
                std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
                std::cerr << " read in Menu object" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool sigrid::MenuContainer::loadHeaders(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            headerNames.push_back(s);
            loadHeaderItems(is);
        }
    }
    return true;
}

bool sigrid::MenuContainer::loadHeaderItems(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            loadMenuItem(is, s);
        }
    }
    return true;
}

bool sigrid::MenuContainer::loadMenuItem(std::istream& is, const std::string& displayName){

    std::string s = sigrid_config::readString(is);
    if(s != "["){
        sigrid::MenuItemContainer item;
        item.headerId = headerNames.size()-1;
        item.displayNames.push_back(displayName);
        item.actionNames.push_back(s);
        menuItems.push_back(item);
    }
    else{
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            sigrid::MenuItemContainer item;
            item.headerId = headerNames.size()-1;
            item.keyName = displayName;
            item.displayNames.push_back(s);
            item.actionNames.push_back(sigrid_config::readString(is));
            item.displayNames.push_back(sigrid_config::readString(is));
            item.actionNames.push_back(sigrid_config::readString(is));
            menuItems.push_back(item);
        }
    }
    return true;
}