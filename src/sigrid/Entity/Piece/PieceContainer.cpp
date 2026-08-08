#include "sigrid/Entity/Piece/PieceContainer.h"

#include <iostream>

using namespace sigrid;

bool PieceContainer::load(InputStream& is){

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

std::ostream& sigrid::operator<<(std::ostream &out, const PieceContainer &piece)
{
    out << "["
        << "\n    notation: " << piece.name
        << "\n    style: " << piece.style
        << "\n    imageFilename: " << piece.filename
        << "\n  ]";

    return out;
}