#include "sigrid/Menu/MenuContainer.h"

#include <iostream>

#include "sigrid/utilities/lists/listLoaders/LoadNamedContainers.h"
#include "sigrid/utilities/lists/listSavers/ListSaver.h"

bool sigrid::MenuContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "MenuContainer: Failed to read initial \"[\"."
            << " Failed to load MenuContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "MenuContainer: Failed to read string."
                << " Failed to load MenuContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "pin:"){

            const auto isPinned_o = is.readToggle();
            if(isPinned_o == std::nullopt){

                std::cerr << "MenuContainer: Failed to read toggle for pin."
                    << " Failed to load MenuContainer" << std::endl;
                return false;
            }
            isPinned = isPinned_o.value();
            showItems = isPinned;
        }
        else if(s == "font:"){

            const auto fontName_o = is.readString();
            if(fontName_o == std::nullopt){

                std::cerr << "MenuContainer: Failed to read string for font."
                    << " Failed to load MenuContainer" << std::endl;
                return false;
            }
            fontName = fontName_o.value();
        }
        else if(s == "title:"){

            const auto title_o = is.readString();
            if(title_o == std::nullopt){

                std::cerr << "MenuContainer: Failed to read string for title."
                    << " Failed to load MenuContainer" << std::endl;
                return false;
            }
            title = title_o.value();
        }
        else if(s == "headers:"){

            if(!(sigrid::loadNamedContainers<HeaderContainer>(headers, is))){

                std::cerr << "MenuContainer: Failed to load headers."
                    << " Failed to load MenuContainer" << std::endl;
                return false;
            }
        }
        else{
            std::cerr << "MenuContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load MenuContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::MenuContainer::getString(const int& indentLevel){

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String pinString;
    if(this->isPinned){
        pinString = "ON";
    }
    else{
        pinString = "OFF";
    }

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("pin: ");
    out.append(pinString);

    out.append("\n");
    out.append(indent1);
    out.append("font: ");
    out.append(this->fontName);

    out.append("\n");
    out.append(indent1);
    out.append("title: ");
    out.append(this->title);

    out.append("\n");
    out.append(indent1);
    out.append("headers: ");
    out.append(sigrid::ListSaver(this->headers).getMultiLineString(indentLevel+1));

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}