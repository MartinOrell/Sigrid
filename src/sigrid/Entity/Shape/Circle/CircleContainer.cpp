#include "sigrid/Entity/Shape/Circle/CircleContainer.h"

#include <iostream>
#include <sstream>

#include "sigrid/utilities/String/String.h"

bool sigrid::CircleContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "CircleContainer: Failed to read initial \"[\"."
            << " Failed to load CircleContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "CircleContainer: Failed to read string."
                << " Failed to load CircleContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "diameter:"){

            const auto diameter_o = is.readFloat();
            if(diameter_o == std::nullopt){

                std::cerr << "CircleContainer: Failed to read float for diameter."
                    << " Failed to load CircleContainer" << std::endl;
                return false;
            }
            diameter = diameter_o.value();
        }
        else{
            std::cerr << "CircleContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load CircleContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::CircleContainer::getString(const int& indentLevel) const{

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String diameterString;
    {
        std::ostringstream ss;
        ss << this->diameter;
        diameterString.set(std::move(ss.str()));
    }

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("diameter: ");
    out.append(diameterString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}