#include "sigrid/Entity/Piece/PieceContainer.h"

#include <iostream>

bool sigrid::PieceContainer::load(InputStream& is){

    while(auto string_o = is.readString()){
        
        if(string_o == std::nullopt){

            std::cerr << "PieceContainer: Failed to read string."
                << " Failed to load PieceContainer" << std::endl;
            return false;
        }
        sigrid::String s = string_o.value();
        if(s == "]"){
            break;
        }
        else if(s == "notation:"){
            auto name_o = is.readString();
            if(name_o == std::nullopt){

                std::cerr << "PieceContainer: Failed to read notation."
                    << " Failed to load PieceContainer" << std::endl;
                return false;
            }
            name = name_o.value();
        }
        else if(s == "style:"){
            auto style_o = is.readString();
            if(style_o == std::nullopt){

                std::cerr << "PieceContainer: Failed to read style."
                    << " Failed to load PieceContainer" << std::endl;
                return false;
            }
            style = style_o.value();
        }
        else if(s == "imageFilename:"){
            auto filename_o = is.readString();
            if(filename_o == std::nullopt){

                std::cerr << "PieceContainer: Failed to read imageFilename"
                    << " Failed to load PieceContainer" << std::endl;
                return false;
            }
            filename = filename_o.value();
        }
        else{
            std::cerr << "PieceContainer: Unknown key: \"" << s << "\".";
            std::cerr << " Failed to load PieceContainer" << std::endl;
            return false;
        }
    }

    return true;
}

sigrid::String sigrid::PieceContainer::getString(const int& indentLevel) const{

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
    out.append("notation: ");
    out.append(this->name);

    out.append("\n");
    out.append(indent1);
    out.append("style: ");
    out.append(this->style);

    out.append("\n");
    out.append(indent1);
    out.append("imageFilename: ");
    out.append(this->filename);

    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}