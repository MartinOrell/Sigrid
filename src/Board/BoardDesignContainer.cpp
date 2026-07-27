#include "BoardDesignContainer.h"

#include <iostream>

#include "Config/IO.h"
#include "Config/LoadContainers.h"

bool sigrid::BoardDesignContainer::load(std::istream& is){

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
        else if(s == "Tile:"){

            if(!tile.load(is)){
                return false;
            }
        }
        else if(s == "Arrow:"){

            if(!arrow.load(is)){
                return false;
            }
        }
        else if(s == "Circle:"){

            if(!circle.load(is)){
                return false;
            }
        }
        else if(s == "CoordLabels:"){
            sigrid_config::loadContainers<BoardLabelContainer>(labels, is);
        }
        else if(s == "Border:"){
            loadBorder(is);
        }
        else if(s == "TurnToken:"){
            loadTurnToken(is);
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load BoardDesignContainer" << std::endl;
            return false;
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadBorder(std::istream& is){

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
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return false;
            }
            border = isVisible_o.value();
        }
        else if(s == "thickness:"){

            const auto borderThickness_o = sigrid_config::readFloat(is);
            if(borderThickness_o == std::nullopt){
                return false;
            }
            borderThickness = borderThickness_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load border" << std::endl;
            return false;
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadTurnToken(std::istream& is){

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
        else if(s == "visibility:"){

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return false;
            }
            turnToken = isVisible_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load turn token" << std::endl;
            return false;
        }
    }
    return true;
}