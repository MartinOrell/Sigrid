#include "sigrid/Menu/MenuContainer.h"

#include <iostream>

#include "sigrid/Config/IO.h"
#include "sigrid/Config/LoadNamedContainers.h"

bool sigrid::MenuContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){

        std::cerr << "MenuContainer: Failed to read initial \"[\"."
            << " Failed to load MenuContainer" << std::endl;
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "MenuContainer: Failed to read string."
                << " Failed to load MenuContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "pin:"){

            const auto isPinned_o = sigrid_config::readToggle(is);
            if(isPinned_o == std::nullopt){

                std::cerr << "MenuContainer: Failed to read toggle for pin."
                    << " Failed to load MenuContainer" << std::endl;
                return false;
            }
            isPinned = isPinned_o.value();
            showItems = isPinned;
        }
        else if(s == "font:"){

            const auto fontName_o = sigrid_config::readString(is);
            if(fontName_o == std::nullopt){

                std::cerr << "MenuContainer: Failed to read string for font."
                    << " Failed to load MenuContainer" << std::endl;
                return false;
            }
            fontName = fontName_o.value();
        }
        else if(s == "title:"){

            const auto title_o = sigrid_config::readString(is);
            if(title_o == std::nullopt){

                std::cerr << "MenuContainer: Failed to read string for title."
                    << " Failed to load MenuContainer" << std::endl;
                return false;
            }
            title = title_o.value();
        }
        else if(s == "headers:"){

            if(!(sigrid_config::loadNamedContainers<HeaderContainer>(headers, is))){

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