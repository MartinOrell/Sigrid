#include "BoardDesignContainer.h"

#include <iostream>

#include "Config/IO.h"

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

bool sigrid::BoardDesignContainer::loadArrow(std::istream& is, int& defaultArrowColorId){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "thickness:"){
                is >> arrowThickness;
            }
            else if(s == "headSize:"){
                is >> arrowHeadSize;
            }
            else if(s == "defaultColorId:"){
                is >> defaultArrowColorId;
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

bool sigrid::BoardDesignContainer::loadCircle(std::istream& is, int& defaultCircleColorId){

    std::string s = sigrid_config::readString(is);
    if(s == "["){
        for(s = sigrid_config::readString(is); s != "]"; s = sigrid_config::readString(is)){
            if(s == "diameter:"){
                is >> circleDiameter;
            }
            else if(s == "defaultColorId:"){
                is >> defaultCircleColorId;
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