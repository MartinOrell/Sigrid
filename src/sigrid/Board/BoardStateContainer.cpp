#include "sigrid/Board/BoardStateContainer.h"

#include <fstream>
#include <iostream>

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/lists/listLoaders/LoadValues.h"

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

    clear();
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

            if(!sigrid::loadValues<int>(repeatTileColorIds, is)){

                std::cerr << "BoardStateContainer: Failed to load RepeatTileColors."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
        }
        else if(key == "Piece:"){

            sigrid::PieceDataContainer pieceContainer;
            if(!pieceContainer.load(is)){

                std::cerr << "BoardStateContainer: Failed to load Piece."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }

            logicPieces.push_back(pieceContainer);
        }
        else if(key == "Circle:"){

            sigrid::CircleDataContainer circleContainer;
            if(!circleContainer.load(is)){

                std::cerr << "BoardStateContainer: Failed to load Circle."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }

            logicCircles.push_back(circleContainer);
        }
        else if(key == "Arrow:"){

            sigrid::ArrowDataContainer arrowContainer;
            if(!arrowContainer.load(is)){

                std::cerr << "BoardStateContainer: Failed to load Arrow."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }

            logicArrows.push_back(arrowContainer);
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

std::ostream& sigrid::operator<<(std::ostream& out, const BoardStateContainer& boardState){

    out << "Columns: " << boardState.columns << "\n";
    out << "Rows: " << boardState.rows << "\n";
    out << "RepeatTileColors: [";

    for(auto& tileId: boardState.repeatTileColorIds){
        out << " " << tileId;
    }
    out << " ]";

    for(const auto& pieceData: boardState.logicPieces){
        out << "\n" << pieceData;
    }

    for(const auto& circleData: boardState.logicCircles){
        out << "\n" << circleData;
    }

    for(const auto& arrowData: boardState.logicArrows){
        out << "\n" << arrowData;
    }
    return out;
}

void sigrid::BoardStateContainer::clear(){

    repeatTileColorIds.clear();
    logicPieces.clear();
    logicCircles.clear();
    logicArrows.clear();
}