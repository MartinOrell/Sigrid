#include "sigrid/Board/BoardStateContainer.h"

#include <fstream>
#include <iostream>

#include "sigrid/utilities/InputStream/InputStream.h"

using namespace sigrid;


bool BoardStateContainer::load(const sigrid::String& filename){

    sigrid::InputStream is;
    {
        std::ifstream ifs(filename.getStdString());

        if(!ifs.is_open()){
            std::cerr << "BoardStateContainer: Failed to open file: \""
                << filename << "\"."
                << " Failed to load BoardStateContainer" << std::endl;
            return false;
        }

        is.set(std::move(ifs));
    }

    this->filename = filename;

    while(!(is.isEndOfFile())){

        const auto key_o = is.readString();
        if(key_o == std::nullopt){

            std::cerr << "BoardStateContainer: Failed to read string."
                << " Failed to load BoardStateContainer from file: \""
                << filename << "\"" << std::endl;
            return false;
        }
        const sigrid::String& key = key_o.value();

        if(key == "Columns:"){

            const auto columns_o = is.readInt();
            if(columns_o == std::nullopt){

                std::cerr << "BoardStateContainer: Failed to read columns."
                << " Failed to load BoardStateContainer from file: \""
                << filename << "\"" << std::endl;
                return false;
            }
            columns = columns_o.value();
        }
        else if(key == "Rows:"){

            const auto rows_o = is.readInt();
            if(rows_o == std::nullopt){

                std::cerr << "BoardStateContainer: Failed to read rows."
                << " Failed to load BoardStateContainer from file: \""
                << filename << "\"" << std::endl;
                return false;
            }
            rows = rows_o.value();
        }
        else if(key == "RepeatTileColors:"){

            for(int i = 0; i < 2; i++){
                auto colorId_o = is.readInt();
                if(colorId_o == std::nullopt){

                    std::cerr << "BoardStateContainer: Failed to read colorId for RepeatTileColors."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                    return false;
                }
                repeatTileColorIds.push_back(colorId_o.value());
            }
        }
        else if(key == "Piece:"){

            sigrid::PieceDataContainer pieceContainer;

            auto colorId_o = is.readInt();
            if(colorId_o == std::nullopt){

                std::cerr << "BoardStateContainer: Failed to read colorId for Piece."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                    return false;
            }
            pieceContainer.colorId = colorId_o.value();

            {
                auto name_o = is.readString();
                if(name_o == std::nullopt){

                    std::cerr << "BoardStateContainer: Failed to read Piece name."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                    return false;
                }
                pieceContainer.name = name_o.value(); 
            }
            
            {
                auto positionString_o = is.readString();
                if(positionString_o == std::nullopt){

                    std::cerr << "BoardStateContainer: Failed to read Piece position string."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                    return false;
                }
                pieceContainer.position = positionString_o.value();
            }
            logicPieces.push_back(pieceContainer);
        }
        else if(key == "Circle:"){

            sigrid::CircleDataContainer circleContainer;

            auto colorId_o = is.readInt();
            if(colorId_o == std::nullopt){

                std::cerr << "BoardStateContainer: Failed to read colorId for Circle."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                    return false;
            }
            circleContainer.colorId = colorId_o.value();

            {
                auto positionString_o = is.readString();
                if(positionString_o == std::nullopt){

                    std::cerr << "BoardStateContainer: Failed to read Circle position string."
                        << " Failed to load BoardStateContainer from file: \""
                        << filename << "\"" << std::endl;
                    return false;
                }
                circleContainer.position = positionString_o.value();
            }
            logicCircles.push_back(circleContainer);
        }
        else if(key == "ImageFilename:"){

            auto imageFilename_o = is.readString();
            if(imageFilename_o == std::nullopt){

                std::cerr << "BoardStateContainer: Failed to read imageFilename."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            imageFilename = imageFilename_o.value();
        }
        else{
            std::cerr << "BoardStateContainer: Unknown key: \"" << key << "\"."
                << " Failed to load BoardStateContainer from file: \""
                << filename << "\"" << std::endl;
            return false;
        }
    }
    return true;
}