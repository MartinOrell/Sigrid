#include "Entity/Piece/PieceContainer.h"

#include <iostream>

#include "Config/IO.h"

using namespace sigrid;

bool PieceContainer::load(std::istream& is){

    while(auto string_o = sigrid_config::readString(is)){
        
        if(string_o == std::nullopt){

            std::cerr << "PieceContainer: Failed to read string."
                << " Failed to load PieceContainer" << std::endl;
            return false;
        }
        std::string s = string_o.value();
        if(s == "]"){
            break;
        }
        else if(s == "notation:"){
            auto name_o = sigrid_config::readString(is);
            if(name_o == std::nullopt){

                std::cerr << "PieceContainer: Failed to read notation."
                    << " Failed to load PieceContainer" << std::endl;
                return false;
            }
            name = name_o.value();
        }
        else if(s == "style:"){
            auto style_o = sigrid_config::readString(is);
            if(style_o == std::nullopt){

                std::cerr << "PieceContainer: Failed to read style."
                    << " Failed to load PieceContainer" << std::endl;
                return false;
            }
            style = style_o.value();
        }
        else if(s == "imageFilename:"){
            auto filename_o = sigrid_config::readString(is);
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