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

            const auto label_o = readLabel(is);
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

std::optional<sigrid::BoardLabelContainer> sigrid::BoardDesignContainer::readLabel(std::istream& is){

    sigrid::BoardLabelContainer label;
    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){
            return std::nullopt;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "position:"){

            const auto positionString_o = sigrid_config::readString(is);
            if(positionString_o == std::nullopt){
                return std::nullopt;
            }
            const std::string& positionString = positionString_o.value();

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

            const auto isVisible_o = sigrid_config::readVisibility(is);
            if(isVisible_o == std::nullopt){
                return std::nullopt;
            }
            label.isVisible = isVisible_o.value();
        }
        else if(s == "size:"){

            const auto size_o = sigrid_config::readPercentage(is);
            if(size_o == std::nullopt){
                return std::nullopt;
            }
            label.size = size_o.value();
        }
        else if(s == "font:"){

            const auto font_o = sigrid_config::readString(is);
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