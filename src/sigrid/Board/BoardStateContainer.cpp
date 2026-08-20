#include "sigrid/Board/BoardStateContainer.h"

#include <fstream>
#include <iostream>

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/lists/listLoaders/LoadValues.h"

bool sigrid::BoardStateContainer::load(const sigrid::String& filename){

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
            this->columns = columns_o.value();
        }
        else if(key == "Rows:"){

            const auto rows_o = is.readInt();
            if(rows_o == std::nullopt){

                std::cerr << "BoardStateContainer: Failed to read rows."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            this->rows = rows_o.value();
        }
        else if(key == "RepeatTileColors:"){

            if(!sigrid::loadValues<int>(this->repeatTileColorIds, is)){

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

            this->logicPieces.push_back(pieceContainer);
        }
        else if(key == "Circle:"){

            sigrid::CircleDataContainer circleContainer;
            if(!circleContainer.load(is)){

                std::cerr << "BoardStateContainer: Failed to load Circle."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }

            this->logicCircles.push_back(circleContainer);
        }
        else if(key == "Arrow:"){

            sigrid::ArrowDataContainer arrowContainer;
            if(!arrowContainer.load(is)){

                std::cerr << "BoardStateContainer: Failed to load Arrow."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }

            this->logicArrows.push_back(arrowContainer);
        }
        else if(key == "TurnToMove:"){

            const auto turnToMove_o = is.readInt();
            if(turnToMove_o == std::nullopt){

                std::cerr << "BoardStateContainer: Failed to read turnToMove."
                    << " Failed to load BoardStateContainer from file: \""
                    << filename << "\"" << std::endl;
                return false;
            }
            this->turnToMove = turnToMove_o.value();
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

sigrid::String sigrid::BoardStateContainer::getString(const int& indentLevel) const{

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }

    sigrid::String columnsString;
    columnsString.set(std::to_string(this->columns));

    sigrid::String rowsString;
    rowsString.set(std::to_string(this->rows));

    sigrid::String turnToMoveString;
    turnToMoveString.set(std::to_string(this->turnToMove));

    sigrid::String out;

    out.append("Columns: ");
    out.append(columnsString);

    out.append("\n");
    out.append(indent0);
    out.append("Rows: ");
    out.append(rowsString);

    if(this->repeatTileColorIds.size() > 0){
        out.append("\n");
        out.append(indent0);
        out.append("RepeatTileColors: [");
        for(auto& tileId: this->repeatTileColorIds){

            sigrid::String tileIdString;
            tileIdString.set(std::to_string(tileId));

            out.append(" ");
            out.append(tileIdString);
        }
        out.append(" ]");
    }
    
    for(const auto& pieceData: this->logicPieces){
        out.append("\n");
        out.append(indent0);
        out.append("Piece: ");
        out.append(pieceData.getString());
    }

    for(const auto& circleData: this->logicCircles){
        out.append("\n");
        out.append(indent0);
        out.append("Circle: ");
        out.append(circleData.getString());
    }

    for(const auto& arrowData: this->logicArrows){
        out.append("\n");
        out.append(indent0);
        out.append("Arrow: ");
        out.append(arrowData.getString());
    }

    out.append("\n");
    out.append(indent0);
    out.append("TurnToMove: ");
    out.append(turnToMoveString);

    return out;
}

void sigrid::BoardStateContainer::clear(){

    repeatTileColorIds.clear();
    logicPieces.clear();
    logicCircles.clear();
    logicArrows.clear();
    turnToMove = 0;
}