#include "MenuContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::MenuContainer::load(std::istream& is){

    auto string_o = sigrid_config::readString(is);
    if(string_o == std::nullopt){
        return false;
    }
    std::string s = string_o.value();
    if(s == "["){
        while(string_o = sigrid_config::readString(is)){
            
            if(string_o == std::nullopt){
                return false;
            }
            s = string_o.value();
            if(s == "]"){
                break;
            }
            else if(s == "pin:"){
                auto isPinned_o = sigrid_config::readToggle(is);
                if(isPinned_o == std::nullopt){
                    return false;
                }
                isPinned = isPinned_o.value();
                showItems = isPinned;
            }
            else if(s == "font:"){
                auto fontName_o = sigrid_config::readString(is);
                if(fontName_o == std::nullopt){
                    return false;
                }
                fontName = fontName_o.value();
            }
            else if(s == "title:"){
                auto title_o = sigrid_config::readString(is);
                if(title_o == std::nullopt){
                    return false;
                }
                title = title_o.value();
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

    auto string_o = sigrid_config::readString(is);
    if(string_o == std::nullopt){
        return false;
    }
    std::string s = string_o.value();
    if(s == "["){
        while(string_o = sigrid_config::readString(is)){
            
            if(string_o == std::nullopt){
                return false;
            }
            s = string_o.value();
            if(s == "]"){
                break;
            }
            headerNames.push_back(s);
            loadHeaderItems(is);
        }
    }
    return true;
}

bool sigrid::MenuContainer::loadHeaderItems(std::istream& is){

    auto string_o = sigrid_config::readString(is);
    if(string_o == std::nullopt){
        return false;
    }
    std::string s = string_o.value();
    if(s == "["){
        while(string_o = sigrid_config::readString(is)){
            
            if(string_o == std::nullopt){
                return false;
            }
            s = string_o.value();
            if(s == "]"){
                break;
            }
            loadMenuItem(is, s);
        }
    }
    return true;
}

bool sigrid::MenuContainer::loadMenuItem(std::istream& is, const std::string& displayName){

    auto string_o = sigrid_config::readString(is);
    if(string_o == std::nullopt){
        return false;
    }
    std::string s = string_o.value();
    if(s != "["){
        sigrid::MenuItemContainer item;
        item.headerId = headerNames.size()-1;
        item.displayNames.push_back(displayName);
        item.actionNames.push_back(s);
        menuItems.push_back(item);
    }
    else{
        while(string_o = sigrid_config::readString(is)){
            
            if(string_o == std::nullopt){
                return false;
            }
            s = string_o.value();
            if(s == "]"){
                break;
            }
            sigrid::MenuItemContainer item;
            item.headerId = headerNames.size()-1;
            item.keyName = displayName;
            item.displayNames.push_back(s);

            {
                auto actionName_o = sigrid_config::readString(is);
                if(actionName_o == std::nullopt){
                    return false;
                }
                item.actionNames.push_back(actionName_o.value());
            }
            
            {
                auto displayName_o = sigrid_config::readString(is);
                if(displayName_o == std::nullopt){
                    return false;
                }
                item.displayNames.push_back(displayName_o.value());
            }
            
            {
                auto actionName_o = sigrid_config::readString(is);
                if(actionName_o == std::nullopt){
                    return false;
                }
                item.actionNames.push_back(actionName_o.value());
            }
            menuItems.push_back(item);
        }
    }
    return true;
}