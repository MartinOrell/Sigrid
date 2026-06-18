#include "BoardDataContainer.h"

#include <fstream>
#include <iostream>

using namespace sigrid;


bool BoardDataContainer::load(const std::string& filename){
    std::ifstream ifs(filename);

    if(!ifs.is_open()){
        std::cerr << "BoardDataContainer: Failed to open board from file: " << filename;
        return false;
    }

    this->filename = filename;

    try{
        std::string key;
        while(ifs >> key){

            if(key == "Columns:"){
                ifs >> columns;
            }
            else if(key == "Rows:"){
                ifs >> rows;
            }
            else if(key == "RepeatTileColors:"){
                int colorId;
                ifs >> colorId;
                repeatTileColorIds.push_back(colorId);
                ifs >> colorId;
                repeatTileColorIds.push_back(colorId);
            }
            else if(key == "Piece:"){
                sigrid::PieceDataContainer pieceContainer;
                ifs >> pieceContainer.colorId;
                ifs >> pieceContainer.name;
                ifs >> pieceContainer.position;
                logicPieces.push_back(pieceContainer);
            }
            else if(key == "Circle:"){
                sigrid::CircleDataContainer circleContainer;
                ifs >> circleContainer.colorId;
                ifs >> circleContainer.position;
                logicCircles.push_back(circleContainer);
            }
            else if(key == "ImageFilename:"){
                ifs >> imageFilename;
            }
            else{
                std::cerr << "BoardDataContainer: Unknown key: " << key << std::endl;
                std::cerr << "found in board file: " << filename << std::endl;
            }
        }
    }
    catch(...){
        std::cerr << "BoardDataContainer: Failed reading board from file: " << filename << std::endl;
        return false;
    }
    return true;
}