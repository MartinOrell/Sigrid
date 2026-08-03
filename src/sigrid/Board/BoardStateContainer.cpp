#include "sigrid/Board/BoardStateContainer.h"

#include <fstream>
#include <iostream>

using namespace sigrid;


bool BoardStateContainer::load(const sigrid::String& filename){

    std::ifstream ifs(filename.getStdString());

    if(!ifs.is_open()){
        std::cerr << "BoardStateContainer: Failed to open board from file: " << filename;
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
                {
                    std::string stdName;
                    ifs >> stdName;
                    pieceContainer.name.set(std::move(stdName));    
                }
                
                {
                    std::string stdPosition;
                    ifs >> stdPosition;
                    pieceContainer.position.set(std::move(stdPosition));
                }
                logicPieces.push_back(pieceContainer);
            }
            else if(key == "Circle:"){
                sigrid::CircleDataContainer circleContainer;
                ifs >> circleContainer.colorId;
                {
                    std::string stdPosition;
                    ifs >> stdPosition;
                    circleContainer.position.set(std::move(stdPosition));
                }
                logicCircles.push_back(circleContainer);
            }
            else if(key == "ImageFilename:"){
                std::string imageFilenameStdString;
                ifs >> imageFilenameStdString;
                imageFilename.set(std::move(imageFilenameStdString));
            }
            else{
                std::cerr << "BoardStateContainer: Unknown key: " << key << std::endl;
                std::cerr << "found in board file: " << filename << std::endl;
            }
        }
    }
    catch(...){
        std::cerr << "BoardStateContainer: Failed reading board from file: " << filename << std::endl;
        return false;
    }
    return true;
}