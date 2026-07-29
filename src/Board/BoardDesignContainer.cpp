#include "BoardDesignContainer.h"

#include <iostream>

#include "Config/IO.h"
#include "Config/LoadContainers.h"

bool sigrid::BoardDesignContainer::load(std::istream& is){

    if(sigrid_config::readString(is) != "["){

        std::cerr << "BoardDesignContainer: Failed to read initial \"[\"."
            << " Failed to load BoardDesignContainer" << std::endl;
        return false;
    }

    while(const auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "BoardDesignContainer: Failed to read string."
                << " Failed to load BoardDesignContainer" << std::endl;
            return false;
        }
        const std::string& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "Tile:"){

            if(!tile.load(is)){

                std::cerr << "BoardDesignContainer: Failed to load Tile."
                    << " Failed to load BoardDesignContainer" << std::endl;
                return false;
            }
        }
        else if(s == "Arrow:"){

            if(!arrow.load(is)){

                std::cerr << "BoardDesignContainer: Failed to load Arrow."
                    << " Failed to load BoardDesignContainer" << std::endl;
                return false;
            }
        }
        else if(s == "Circle:"){

            if(!circle.load(is)){

                std::cerr << "BoardDesignContainer: Failed to load Circle."
                    << " Failed to load BoardDesignContainer" << std::endl;
                return false;
            }
        }
        else if(s == "CoordLabels:"){

            if(!sigrid_config::loadContainers<BoardLabelContainer>(labels, is)){

                std::cerr << "BoardDesignContainer: Failed to load CoorcLabels."
                    << " Failed to load BoardDesignContainer" << std::endl;
                return false;
            }
        }
        else if(s == "Border:"){

            if(!border.load(is)){

                std::cerr << "BoardDesignContainer: Failed to load Border."
                    << " Failed to load BoardDesignContainer" << std::endl;
                return false;
            }
        }
        else if(s == "TurnToken:"){

            if(!turnToken.load(is)){

                std::cerr << "BoardDesignContainer: Failed to load TurnToken."
                    << " Failed to load BoardDesignContainer" << std::endl;
                return false;
            }
        }
        else{
            std::cerr << "BoardDesignContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load BoardDesignContainer" << std::endl;
            return false;
        }
    }
    return true;
}