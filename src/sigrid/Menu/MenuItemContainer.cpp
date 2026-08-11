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

sigrid::String sigrid::MenuItemContainer::getString(const int& indentLevel) const{

    if(this->displayNames.size() == 0){
        std::cerr << "MenuItemContainer: No displayNames found."
            << " Failed getting string. returning empty list" << std::endl;

        return sigrid::String{"[]"};
    }

    if(this->displayNames.size() == 1){
        
        const auto displayName_o = this->displayNames.front();
        if(displayName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving first displayName."
                << " Failed getting string. returning empty list" << std::endl;
            
            return sigrid::String{"[]"};
        }

        const auto actionName_o = this->actionNames.front();
        if(actionName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving first action."
                << " Failed getting string. returning empty list" << std::endl;
            
            return sigrid::String{"[]"};
        }

        const sigrid::String& displayName = displayName_o.value().get();
        const sigrid::String& actionName = actionName_o.value().get();

        sigrid::String printName;
        if(displayName.find(' ') != std::nullopt){
            printName.set("\"" + std::move(displayName.getStdString()) + "\"");
        }
        else{
            printName.set(std::move(displayName.getStdString()));
        }

        sigrid::String printAction;
        if(actionName.find(' ') != std::nullopt){
            printAction.set("\"" + std::move(actionName.getStdString()) + "\"");
        }
        else{
            printAction.set(std::move(actionName.getStdString()));
        }

        sigrid::String out;
        out.append(printName);
        out.append(" ");
        out.append(printAction);

        return out;
    }

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String out;

    out.append(this->name);
    out.append(" ");
    out.append(" [");

    for(int i = 0; i < this->displayNames.size(); i++){

        const auto displayName_o = this->displayNames.at(i);
        if(displayName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving displayName " << i << "."
                << std::endl;
            continue;
        }

        const auto actionName_o = this->actionNames.at(i);
        if(actionName_o == std::nullopt){
            std::cerr << "MenuItemContainer: Failed receiving action " << i << "."
                << std::endl;
            continue;
        }

        const sigrid::String& displayName = displayName_o.value().get();
        const sigrid::String& actionName = actionName_o.value().get();

        sigrid::String printName;
        if(displayName.find(' ') != std::nullopt){
            printName.set("\"" + std::move(displayName.getStdString()) + "\"");
        }
        else{
            printName.set(std::move(displayName.getStdString()));
        }

        sigrid::String printAction;
        if(actionName.find(' ') != std::nullopt){
            printAction.set("\"" + std::move(actionName.getStdString()) + "\"");
        }
        else{
            printAction.set(std::move(actionName.getStdString()));
        }

        out.append("\n");
        out.append(indent1);
        out.append(printName);
        out.append(" ");
        out.append(printAction);
    }

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}