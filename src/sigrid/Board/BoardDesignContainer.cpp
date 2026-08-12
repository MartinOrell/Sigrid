#include "sigrid/Board/BoardDesignContainer.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/listLoaders/LoadContainers.h"

bool sigrid::BoardDesignContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "BoardDesignContainer: Failed to read initial \"[\"."
            << " Failed to load BoardDesignContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "BoardDesignContainer: Failed to read string."
                << " Failed to load BoardDesignContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

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

            if(!sigrid::loadContainers<BoardLabelContainer>(labels, is)){

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

sigrid::String sigrid::BoardDesignContainer::getString(const int& indentLevel){

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String out;
    
    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("Tile: ");
    out.append(this->tile.getString(indentLevel+1));

    out.append("\n");
    out.append(indent1);
    out.append("Arrow: ");
    out.append("[]");

    out.append("\n");
    out.append(indent1);
    out.append("Circle: ");
    out.append("[]");

    out.append("\n");
    out.append(indent1);
    out.append("CoordLabels: ");
    out.append("[]");

    out.append("\n");
    out.append(indent1);
    out.append("Border: ");
    out.append("[]");

    out.append("\n");
    out.append(indent1);
    out.append("TurnToken: ");
    out.append("[]");

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}