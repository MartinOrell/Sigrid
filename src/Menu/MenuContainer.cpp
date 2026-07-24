#include "MenuContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::MenuContainer::load(std::istream& is){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
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
            loadHeaders(is);
        }
        else{
            std::cerr << "MainWindowConfigContainer: Unknown key: \"" << s << "\"";
            std::cerr << " read in Menu object" << std::endl;
            return false;
        }
    }
    return true;
}

bool sigrid::MenuContainer::loadHeaders(std::istream& is){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
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
        headerNames.push_back(s);
        loadHeaderItems(is);
    }
    return true;
}

bool sigrid::MenuContainer::loadHeaderItems(std::istream& is){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            return false;
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
        loadMenuItem(is, s);
    }
    return true;
}

bool sigrid::MenuContainer::loadMenuItem(std::istream& is, const std::string& displayName){

    {
        const auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        const std::string& s = string_o.value();

        if(s != "["){
            sigrid::MenuItemContainer item;
            item.headerId = headerNames.size()-1;
            item.displayNames.push_back(displayName);
            item.actionNames.push_back(s);
            menuItems.push_back(item);
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
        sigrid::MenuItemContainer item;
        item.headerId = headerNames.size()-1;
        item.keyName = displayName;
        item.displayNames.push_back(s);

        {
            const auto actionName_o = sigrid_config::readString(is);
            if(actionName_o == std::nullopt){
                return false;
            }
            item.actionNames.push_back(actionName_o.value());
        }
        
        {
            const auto displayName_o = sigrid_config::readString(is);
            if(displayName_o == std::nullopt){
                return false;
            }
            item.displayNames.push_back(displayName_o.value());
        }
        
        {
            const auto actionName_o = sigrid_config::readString(is);
            if(actionName_o == std::nullopt){
                return false;
            }
            item.actionNames.push_back(actionName_o.value());
        }
        menuItems.push_back(item);
    }
    return true;
}