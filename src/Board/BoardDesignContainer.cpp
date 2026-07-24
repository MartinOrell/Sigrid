#include "BoardDesignContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::BoardDesignContainer::load(std::istream& is){

    {
        auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s != "["){
            return false;
        }
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

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

    {
        auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s != "["){
            return false;
        }
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "width:"){
            is >> tileWidth;
        }
        else if(s == "height:"){
            is >> tileHeight;
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

    {
        auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s != "["){
            return false;
        }
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();
        if(s == "]"){
            break;
        }
        else if(s == "thickness:"){
            is >> arrowThickness;
        }
        else if(s == "headSize:"){
            is >> arrowHeadSize;
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

    {
        auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s != "["){
            return false;
        }
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "diameter:"){
            is >> circleDiameter;
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

    {
        auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s != "["){
            return false;
        }
    }
    
    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "["){
            auto label_o = readLabel(is);
            if(label_o == std::nullopt){
                return false;
            }
            sigrid::BoardLabelContainer label = label_o.value();
            labels.push_back(label);
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadBorder(std::istream& is){

    {
        auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s != "["){
            return false;
        }
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){
            auto string_o = sigrid_config::readString(is);
            if(string_o == std::nullopt){
                return false;
            }
            std::string visibilityString = string_o.value();
            border = visibilityString == "Visible";
        }
        else if(s == "thickness:"){
            is >> borderThickness;
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

    {
        auto string_o = sigrid_config::readString(is);
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s != "["){
            return false;
        }
    }

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return false;
        }
        std::string s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "visibility:"){

            auto string_o = sigrid_config::readString(is);
            if(string_o == std::nullopt){
                return false;
            }
            std::string visibilityString = string_o.value();
            turnToken = visibilityString == "Visible";
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load turn token" << std::endl;
            return false;
        }
    }
    return true;
}

std::optional<sigrid::BoardLabelContainer> sigrid::BoardDesignContainer::readLabel(std::istream& is){

    sigrid::BoardLabelContainer label;
    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return std::nullopt;
        }
        std::string s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "position:"){

            auto positionString_o = sigrid_config::readString(is);
            if(positionString_o == std::nullopt){
                return std::nullopt;
            }
            std::string positionString = positionString_o.value();
            label.isInside = positionString.substr(0,6) == "inside";
            auto spacePos = positionString.find(' ');
            if(spacePos != std::string::npos){
                std::string positionString2 = positionString.substr(spacePos+1);
                if(positionString2 == "left"){
                    label.position = 0;
                }
                else if(positionString2 == "right"){
                    label.position = 1;
                }
                else if(positionString2 == "top"){
                    label.position = 2;
                }
                else if(positionString2 == "bottom"){
                    label.position = 3;
                }
                else{
                    std::cerr << "BoardDesignContainer: Unknown label position: " << positionString2 << std::endl;
                }
            }
        }
        else if(s == "visibility:"){

            auto visibilityString_o = sigrid_config::readString(is);
            if(visibilityString_o == std::nullopt){
                return std::nullopt;
            }
            std::string visibilityString = visibilityString_o.value();
            label.isVisible = visibilityString == "Visible";
        }
        else if(s == "size:"){

            float size;
            is >> size;
            is.ignore(1);// ignore % sign
            size = size/100.f;
            label.size = size;
        }
        else if(s == "font:"){

            auto font_o = sigrid_config::readString(is);
            if(font_o == std::nullopt){
                return std::nullopt;
            }
            label.font = font_o.value();
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load coordLabel" << std::endl;
        }
    }
    return label;
}