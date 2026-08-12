#include "sigrid/Entity/Tile/TileContainer.h"

#include <iostream>
#include <sstream>

#include "sigrid/utilities/String/String.h"

bool sigrid::TileContainer::load(InputStream& is){

    if(is.readString() != "["){

        std::cerr << "TileContainer: Failed to load initial \"[\"."
            << " Failed to load TileContainer" << std::endl;
        return false;
    }

    while(const auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "TileContainer: Failed to read string."
                << " Failed to load TileContainer" << std::endl;
            return false;
        }
        const sigrid::String& s = string_o.value();

        if(s == "]"){
            break;
        }
        else if(s == "width:"){

            const auto width_o = is.readFloat();
            if(width_o == std::nullopt){

                std::cerr << "TileContainer: Failed to read float for width."
                    << " Failed to load TileContainer" << std::endl;
                return false;
            }
            width = width_o.value();
        }
        else if(s == "height:"){

            const auto height_o = is.readFloat();
            if(height_o == std::nullopt){

                std::cerr << "TileContainer: Failed to read float for height."
                    << " Failed to load TileContainer" << std::endl;
                return false;
            }
            height = height_o.value();
        }
        else{
            std::cerr << "TileContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load tileContainer" << std::endl;
            return false;
        }
    }
    return true;
}

sigrid::String sigrid::TileContainer::getString(const int& indentLevel){

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    sigrid::String widthString;
    {
        std::ostringstream ss;
        ss << this->width;
        widthString.set(std::move(ss.str()));
    }

    sigrid::String heightString;
    {
        std::ostringstream ss;
        ss << this->height;
        heightString.set(std::move(ss.str()));
    }

    sigrid::String out;

    out.append("[");

    out.append("\n");
    out.append(indent1);
    out.append("width: ");
    out.append(widthString);

    out.append("\n");
    out.append(indent1);
    out.append("height: ");
    out.append(heightString);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}