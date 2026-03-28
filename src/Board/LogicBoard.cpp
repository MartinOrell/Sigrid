#include "LogicBoard.h"

#include <iostream>
#include "../Entity/Piece/LogicPiece.h"
#include <cctype>

#include <algorithm>

#include <fstream>

using namespace sigrid;

LogicBoard::LogicBoard(){}

LogicBoard::LogicBoard(const LogicBoard& board)
: m_pieceLayer{board.m_pieceLayer}{
    for(int y = 0; y < board.m_tileLayer.size(); y++){
        std::vector<LogicTile> tileRow;
        for(int x = 0; x < board.m_tileLayer.at(y).size(); x++){
            tileRow.push_back(board.m_tileLayer.at(y).at(x));
        }
        m_tileLayer.push_back(tileRow);
    }
}

LogicBoard::~LogicBoard(){}

bool LogicBoard::init(const BoardDataContainer& data){
    m_repeatTileColorIds = data.repeatTileColorIds;

    if(m_repeatTileColorIds.size() == 0){
        std::cout << "Failed to setup LogicBoard: Default tile colors not set" << std::endl;
        return false;
    }

    for(unsigned int y = 0; y < data.rows; y++){
        std::vector<LogicTile> tileRow;
        for(unsigned int x = 0; x < data.columns; x++){
            tileRow.push_back(LogicTile{m_repeatTileColorIds.at((x+y)%m_repeatTileColorIds.size())});
        }
        m_tileLayer.push_back(tileRow);
    }

    for(const auto pieceContainer : data.logicPieces){

        Coord coord{pieceContainer.position};

        if(coord.y < 0){
            std::cout << "Failed to set piece at " << coord.getNotation() << ", missing row on board" << std::endl;
            continue;
        }
        if(coord.y >= height()){
            std::cout << "Failed to set piece at " << coord.getNotation() << ", missing row on board" << std::endl;
            continue;
        }
        if(coord.x < 0){
            std::cout << "Failed to set piece at " << coord.getNotation() << ", missing column on board" << std::endl;
            continue;
        }
        if(coord.x >= width()){
            std::cout << "Failed to set piece at " << coord.getNotation() << ", missing column on board" << std::endl;
            continue;
        }
        m_pieceLayer.addEntity(coord, LogicPiece(pieceContainer.name, pieceContainer.colorId));
    }

    for(const auto cData : data.logicCircles){

        Coord coord{cData.position};

        if(!isWithinBoard(coord)){
            std::cout << "LogicBoard constructor: Failed to set circle at " << coord.getNotation() << std::endl;
            std::cout << "coordinate is outside of board" << std::endl;
            continue;
        }

        m_pieceLayer.addEntity(coord, LogicCircle{cData.colorId});
    }

    return true;
}

LogicBoard& LogicBoard::operator=(const LogicBoard& rhs){

    m_repeatTileColorIds = rhs.m_repeatTileColorIds;
    m_tileLayer = rhs.m_tileLayer;
    m_pieceLayer = rhs.m_pieceLayer;
    m_arrowLayer = rhs.m_arrowLayer;

    return *this;
}

const unsigned int LogicBoard::width() const{
    return m_tileLayer.at(0).size();
}

const unsigned int LogicBoard::height() const{
    return m_tileLayer.size();
}

bool LogicBoard::isWithinBoard(const Coord& coord) const{
    if(coord.x >= width()){
        return false;
    }
    if(coord.y >= height()){
        return false;
    }
    return true;
}

bool LogicBoard::isEmptyTile(const Coord& coord) const{
    if(!isWithinBoard(coord)){
        return false;
    }
    return m_pieceLayer.getEntityAt(coord) == std::nullopt;
}

std::optional<LogicTile> LogicBoard::getTile(const Coord& coord) const{
    if(!isWithinBoard(coord)){
        return std::nullopt;
    }

    return m_tileLayer.at(coord.y).at(coord.x);
}

std::optional<LogicEntity> LogicBoard::getEntityAt(const Coord& coord) const{
    return m_pieceLayer.getEntityAt(coord);
}

std::optional<LogicArrow> LogicBoard::getArrowAt(const CoordPair& coordPair) const{

    auto arrow_o = m_arrowLayer.getArrow(coordPair);

    if(arrow_o == std::nullopt){
        return std::nullopt;
    }

    return arrow_o.value();
}

std::string LogicBoard::getFen() const{

    std::string fen;

    for(int y = height()-1; y >= 0; y--){
        int i = 0;
        for(int x = 0; x < width();x++){
            auto entity_o = m_pieceLayer.getEntityAt({x,y});
            if(entity_o == std::nullopt
            || !std::holds_alternative<LogicPiece>(entity_o.value())){
                i++;
                continue;
            }
            
            if(i > 0){
                fen.append(std::to_string(i));
                i = 0;
            }
            LogicPiece piece = std::get<LogicPiece>(entity_o.value());
            std::string s = piece.getNotation();
            if(piece.getColorId() == 1){
                s.front() = tolower(s.front());
            }
            fen.append(s);
            
        }
        if(i > 0){
            fen.append(std::to_string(i));
        }
        if(y > 0){
            fen.append("/");
        }
    }

    return fen;
}

bool LogicBoard::addEntity(const Coord& coord, const LogicEntity& entity){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to add entity at " << coord.getNotation() << std::endl;
        std::cout << "The tile is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.getEntityAt(coord) != std::nullopt){
        std::cout << "LogicBoard: Unable to add entity at " << coord.getNotation() << std::endl;
        std::cout << "The tile is already occupied" << std::endl;
        return false;
    }

    m_pieceLayer.addEntity(coord,entity);
    return true;
}

bool LogicBoard::removeEntity(const Coord& coord){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to remove entity at " << coord.getNotation() << std::endl;
        std::cout << "The tile is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.getEntityAt(coord) == std::nullopt){
        std::cout << "LogicBoard: Unable to remove entity at " << coord.getNotation() << std::endl;
        std::cout << "There is no entity there" << std::endl;
        return false;
    }

    m_pieceLayer.removeEntity(coord);
    return true;
}

bool LogicBoard::moveEntity(const Coord& fromCoord, const Coord& toCoord){

    if(fromCoord.x == toCoord.x && fromCoord.y == toCoord.y){
        std::cout << "LogicBoard: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cout << "both coordinates are the same" << std::endl;
        return false;
    }

    if(!isWithinBoard(fromCoord)){
        std::cout << "LogicBoard: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cout << "starting tile is out of bounds" << std::endl;
        return false;
    }

    if(!isWithinBoard(toCoord)){
        std::cout << "LogicBoard: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cout << "destination tile is out of bounds" << std::endl;
        return false;
    }

    if(isEmptyTile(fromCoord)){
        std::cout << "LogicBoard: Unable to move entity from " << fromCoord.getNotation() << std::endl;
        std::cout << "No piece is standing there" << std::endl;
        return false;
    }

    if(!isEmptyTile(toCoord)){
        m_pieceLayer.removeEntity(toCoord);
    }

    m_pieceLayer.moveEntity(fromCoord, toCoord);
    return true;
}

bool LogicBoard::addTileHighlight(const Coord& coord, const int& highlightColorId){
    
    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to add highlight." << std::endl;
        std::cout << "Coord is not a valid tile (value:" << coord.getNotation() << ")" << std::endl;
        return false;
    }

    if(highlightColorId < 0){
        std::cout << "LogicBoard: Unable to add highlight." << std::endl;
        std::cout << "ColorId is not set (value: " << highlightColorId << ")" << std::endl;
        return false;
    }

    m_tileLayer.at(coord.y).at(coord.x).setHighlightColor(highlightColorId);
    return true;
}

bool LogicBoard::removeTileHighlight(const Coord& coord){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to remove highlight." << std::endl;
        std::cout << "Coord is not a valid tile (value:" << coord.getNotation() << ")" << std::endl;
        return false;
    }

    m_tileLayer.at(coord.y).at(coord.x).removeHighlight();
    return true;
}

bool LogicBoard::addArrow(const CoordPair& coordPair, const LogicArrow& arrow){

    if(!isWithinBoard(coordPair.from)){
        std::cout << "LogicBoard: Unable to add arrow from tile: " << coordPair.from.getNotation() << std::endl;
        std::cout << "Starting tile is outside of the board" << std::endl;
        return false;
    }

    if(!isWithinBoard(coordPair.to)){
        std::cout << "LogicBoard: Unable to add arrow to tile: " << coordPair.to.getNotation() << std::endl;
        std::cout << "Destination tile is outside of the board" << std::endl;
        return false;
    }

    if(arrow.getColorId() < 0){
        std::cout << "LogicBoard: Unable to add arrow" << std::endl;
        std::cout << "ColorId is not set (value: " << arrow.getColorId() << ")" << std::endl;
        return false;
    }

    auto occupyingArrow_o = m_arrowLayer.getArrow(coordPair);

    if(occupyingArrow_o != std::nullopt){
        std::cout << "LogicBoard: Unable to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "There is already an arrow there" << std::endl;
        return false;
    }

    m_arrowLayer.addArrow(coordPair, arrow);
    return true;
}


bool LogicBoard::removeArrow(const CoordPair& coordPair){

    auto occupyingArrow_o = m_arrowLayer.getArrow(coordPair);

    if(occupyingArrow_o == std::nullopt){
        std::cout << "LogicBoard: Unable to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "There is no arrow there" << std::endl;
        return false;
    }

    m_arrowLayer.removeArrow(coordPair);
    return true;
}

void LogicBoard::print(){
    std::cout << "Printing board" << std::endl;
    std::cout << "height = " << height() << std::endl;
    std::cout << "width = " << width() << std::endl;
    
    for(int y = 0; y < height(); y++){
        for(int x = 0; x < width(); x++){
            auto entity_o = m_pieceLayer.getEntityAt({x,y});
            if(entity_o == std::nullopt
            || !std::holds_alternative<LogicPiece>(entity_o.value())){
                std::cout << " ";
            }
            else{
                std::cout << std::get<LogicPiece>(entity_o.value()).getNotation();
            }
        }
        std::cout << "\n";
    }
}

void LogicBoard::clear(){
    m_pieceLayer.clear();
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicBoard &board)
{
    out << "Columns: " << board.width() << "\n";
    out << "Rows: " << board.height() << "\n";
    out << "RepeatTileColors:";
    for(const auto& id: board.m_repeatTileColorIds){
        out << " " << id;
    }
    out << board.m_pieceLayer;
    return out;
}
