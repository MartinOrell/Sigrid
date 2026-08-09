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

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::MenuItemContainer& item){
    
    if(item.displayNames.size() == 0){
        std::cerr << "MenuItemContainer: No displayNames found."
            << " printing empty list with << operator" << std::endl; 
        out << "[]";
        return out;
    }

    if(item.displayNames.size() == 1){
        
        const auto displayName_o = item.displayNames.front();
        if(displayName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving first displayName."
                << " printing empty list with << operator" << std::endl;
            out << "[]";
            return out;
        }

        const auto actionName_o = item.actionNames.front();
        if(actionName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving first action."
                << " printing empty list with << operator" << std::endl;
            out << "[]";
            return out;
        }

        const sigrid::String& displayName = displayName_o.value().get();
        const sigrid::String& actionName = actionName_o.value().get();

        std::string printName;
        if(displayName.find(' ') != std::nullopt){
            printName = "\"" + displayName.getStdString() + "\"";
        }
        else{
            printName = displayName.getStdString();
        }

        std::string printAction;
        if(actionName.find(' ') != std::nullopt){
            printAction = "\"" + actionName.getStdString() + "\"";
        }
        else{
            printAction = actionName.getStdString();
        }

        out << printName << " " << printAction;
        return out;
    }

    out << item.name << " [";
    for(int i = 0; i < item.displayNames.size(); i++){

        const auto displayName_o = item.displayNames.at(i);
        if(displayName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving displayName " << i << "."
                << std::endl;
            continue;
        }

        const auto actionName_o = item.actionNames.at(i);
        if(actionName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving action " << i << "."
                << std::endl;
            continue;
        }

        const sigrid::String& displayName = displayName_o.value().get();
        const sigrid::String& actionName = actionName_o.value().get();

        std::string printName;
        if(displayName.find(' ') != std::nullopt){
            printName = "\"" + displayName.getStdString() + "\"";
        }
        else{
            printName = displayName.getStdString();
        }

        std::string printAction;
        if(actionName.find(' ') != std::nullopt){
            printAction = "\"" + actionName.getStdString() + "\"";
        }
        else{
            printAction = actionName.getStdString();
        }

        out << "\n        " << printName << " " << printAction;
    }
    out << "\n      ]";

    return out;
}