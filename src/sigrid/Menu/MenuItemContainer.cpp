#include "sigrid/Menu/MenuItemContainer.h"

#include <iostream>

bool sigrid::MenuItemContainer::load(InputStream& is){

    {
        const auto string_o = is.readString();
        if(string_o == std::nullopt){

            std::cerr << "MenuItemContainer: Failed to read initial [."
                << "\" when it should be \"[\"."
                << " Failed to load MenuItemContainer named \"" << this->name << "\"" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s != "["){
            
            std::cerr << "MenuItemContainer: initial string is \"" << s
                << "\" when it should be \"[\"."
                << " Failed to load MenuItemContainer named \"" << this->name << "\"" << std::endl;
            return false;
        }
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "MenuItemContainer: Failed to read string."
                << " Failed to load MenuItemContainer named \""
                    << this->name << "\"" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            const auto visibilityString_o = is.readString();
            if(visibilityString_o == std::nullopt){

                std::cerr << "MenuItemContainer: Failed to read visibilityString."
                    << " Failed to load MenuItemContainer named \""
                    << this->name << "\"" << std::endl;
                return false;
            }
            const sigrid::String& visibilityString = visibilityString_o.value();
            
            this->isVisible = visibilityString == "Visible";
        }
        else if(s == "text:"){

            auto textString_o = is.readString();
            if(textString_o == std::nullopt){

                std::cerr << "MenuItemContainer: Failed to read textString."
                    << " Failed to load MenuItemContainer named \""
                    << this->name << "\"" << std::endl;
                return false;
            }
            displayNames.push_back(std::move(textString_o.value()));
        }
        else if(s == "action:"){

            auto actionName_o = is.readString();
            if(actionName_o == std::nullopt){

                std::cerr << "MenuItemContainer: Failed to read actionNameString."
                    << " Failed to load MenuItemContainer named \""
                    << this->name << "\"" << std::endl;
                return false;
            }
            actionNames.push_back(std::move(actionName_o.value()));
        }
        else if(s == "["){

            while(const auto string2_o = is.readString()){
        
                if(string2_o == std::nullopt){

                    std::cerr << "MenuItemContainer: Failed to read string."
                        << " Failed to load MenuItemContainer named \""
                        << this->name << "\"" << std::endl;
                    return false;
                }
                const sigrid::String& s2 = string2_o.value();

                if(s2 == "]"){
                    break;
                }
                else if(s2 == "text:"){

                    auto textString_o = is.readString();
                    if(textString_o == std::nullopt){

                        std::cerr << "MenuItemContainer: Failed to read textString."
                            << " Failed to load MenuItemContainer named \""
                            << this->name << "\"" << std::endl;
                        return false;
                    }
                    displayNames.push_back(std::move(textString_o.value()));
                }
                else if(s2 == "action:"){

                    auto actionName_o = is.readString();
                    if(actionName_o == std::nullopt){

                        std::cerr << "MenuItemContainer: Failed to read actionNameString."
                            << " Failed to load MenuItemContainer named \""
                            << this->name << "\"" << std::endl;
                        return false;
                    }
                    actionNames.push_back(std::move(actionName_o.value()));
                }
            }
        }
    }
    return true;
}

sigrid::String sigrid::MenuItemContainer::getString(const int& indentLevel) const{

    if(this->displayNames.size() == 0){
        std::cerr << "MenuItemContainer: No displayNames found."
            << " Failed getting string. returning empty list" << std::endl;

        return sigrid::String{"[]"};
    }

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String containerName;
    if(this->name.find(' ') != std::nullopt){
        containerName.set("\"" + std::move(this->name.getStdString()) + "\"");
    }
    else{
        containerName = this->name;
    }

    sigrid::String visibilityString;
    if(this->isVisible){
        visibilityString = "Visible";
    }
    else{
        visibilityString = "Hidden";
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
            printName = std::move(displayName);
        }

        sigrid::String printAction;
        if(actionName.find(' ') != std::nullopt){
            printAction.set("\"" + std::move(actionName.getStdString()) + "\"");
        }
        else{
            printAction = std::move(actionName);
        }

        sigrid::String out;

        out.append(containerName);
        out.append(" [");

        out.append("\n");
        out.append(indent1);
        out.append("visibility: ");
        out.append(visibilityString);

        out.append("\n");
        out.append(indent1);
        out.append("text: ");
        out.append(printName);

        out.append("\n");
        out.append(indent1);
        out.append("action: ");
        out.append(printAction);

        out.append("\n");
        out.append(indent0);
        out.append("]");

        return out;
    }

    sigrid::String indent2 = indent1;
    indent2.append("  ");

    sigrid::String out;

    out.append(containerName);
    out.append(" [");

    out.append("\n");
    out.append(indent1);
    out.append("visibility: ");
    out.append(visibilityString);

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
            printName = std::move(displayName);
        }

        sigrid::String printAction;
        if(actionName.find(' ') != std::nullopt){
            printAction.set("\"" + std::move(actionName.getStdString()) + "\"");
        }
        else{
            printAction = std::move(actionName);
        }

        out.append("\n");
        out.append(indent1);
        out.append("[");

        out.append("\n");
        out.append(indent2);
        out.append("text: ");
        out.append(printName);

        out.append("\n");
        out.append(indent2);
        out.append("action: ");
        out.append(printAction);

        out.append("\n");
        out.append(indent1);
        out.append("]");
    }

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}