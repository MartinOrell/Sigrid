#include "BoardDesignContainer.h"

#include <iostream>

#include "Config/IO.h"

bool sigrid::BoardDesignContainer::load(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "Tile:"){
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
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadTile(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "width:"){
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
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadArrow(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "thickness:"){
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
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadCircle(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "diameter:"){
                is >> circleDiameter;
            }
            else{
                std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
                std::cerr << ". Failed to load circle" << std::endl;
                return false;
            }
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadCoordLabels(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if( s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "["){
                sigrid::BoardLabelContainer label = readLabel(is);
                labels.push_back(label);
            }
        }
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadBorder(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "visibility:"){
                std::string visibilityString = sigrid_config::readString(is);
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
    }
    return true;
}

bool sigrid::BoardDesignContainer::loadTurnToken(std::istream& is){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "visibility:"){
                std::string visibilityString = sigrid_config::readString(is);
                turnToken = visibilityString == "Visible";
            }
            else{
                std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
                std::cerr << ". Failed to load turn token" << std::endl;
                return false;
            }
        }
    }
    return true;
}

sigrid::BoardLabelContainer sigrid::BoardDesignContainer::readLabel(std::istream& is){

    sigrid::BoardLabelContainer label;
    for(std::string s = sigrid_config::readString(is);s != "]"; s = sigrid_config::readString(is)){
        if(s == "position:"){
            std::string positionString = sigrid_config::readString(is);
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
            std::string visibilityString = sigrid_config::readString(is);
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
            label.font = sigrid_config::readString(is);
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\"";
            std::cerr << ". Failed to load coordLabel" << std::endl;
        }
    }
    return label;
}