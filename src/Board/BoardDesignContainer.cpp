#include "BoardDesignContainer.h"

#include <iostream>

#include "Config/IO.h"

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
            loadTile(is);
        }
        else if(s == "Arrow:"){
            loadArrow(is);
        }
        else if(s == "Circle:"){
            loadCircle(is);
        }
        else if(s == "CoordLabels:"){
            loadCoordLabels(is);
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

bool sigrid::BoardDesignContainer::loadTile(std::istream& is){

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
        else if(s == "width:"){

            const auto tileWidth_o = sigrid_config::readFloat(is);
            if(tileWidth_o == std::nullopt){
                return false;
            }
            tileWidth = tileWidth_o.value();
        }
        else if(s == "height:"){

            const auto tileHeight_o = sigrid_config::readFloat(is);
            if(tileHeight_o == std::nullopt){
                return false;
            }
            tileHeight = tileHeight_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load tile" << std::endl;
            return false;
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadArrow(std::istream& is){

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
        else if(s == "thickness:"){

            const auto arrowThickness_o = sigrid_config::readFloat(is);
            if(arrowThickness_o == std::nullopt){
                return false;
            }
            arrowThickness = arrowThickness_o.value();
        }
        else if(s == "headSize:"){

            const auto arrowHeadSize_o = sigrid_config::readFloat(is);
            if(arrowHeadSize_o == std::nullopt){
                return false;
            }
            arrowHeadSize = arrowHeadSize_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load arrow" << std::endl;
            return false;
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadCircle(std::istream& is){

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
        else if(s == "diameter:"){

            const auto circleDiameter_o = sigrid_config::readFloat(is);
            if(circleDiameter_o == std::nullopt){
                return false;
            }
            circleDiameter = circleDiameter_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load circle" << std::endl;
            return false;
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadCoordLabels(std::istream& is){

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
        else if(s == "["){

            BoardLabelContainer newLabel;
            if(!newLabel.load(is)){
                return false;
            }
            labels.push_back(std::move(newLabel));
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