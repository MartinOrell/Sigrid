#include "sigrid/Board/BoardContainer.h"

#include <iostream>

bool sigrid::BoardContainer::load(sigrid::InputStream& is){

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "BoardContainer: Failed to read string."
                << " Failed to load BoardContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "["){
            continue;
        }
        else if(s == "]"){
            break;
        }
        else if(s == "stateFilename:"){

            const auto stateFilename_o = is.readString();
            if(stateFilename_o == std::nullopt){

                std::cerr << "BoardContainer: Failed to read string for stateFilename."
                    << " Failed to load BoardContainer" << std::endl;
                return false;
            }
            this->stateFilename = stateFilename_o.value();
        }
        else if(s == "imageFilename:"){

            const auto imageFilename_o = is.readString();
            if(imageFilename_o == std::nullopt){

                std::cerr << "BoardContainer: Failed to read string for imageFilename."
                    << " Failed to load BoardContainer" << std::endl;
                return false;
            }
            this->imageFilename = imageFilename_o.value();
        }
        else{
            std::cerr << "BoardContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load BoardContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::BoardContainer::getString(const int& indentLevel) const{

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String out;

    out.append("[");

    if(this->stateFilename.length() > 0){
        out.append("\n");
        out.append(indent1);
        out.append("stateFilename: ");
        out.append(this->stateFilename);
    }

    if(this->imageFilename.length() > 0){
        out.append("\n");
        out.append(indent1);
        out.append("imageFilename: ");
        out.append(this->imageFilename);
    }

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}