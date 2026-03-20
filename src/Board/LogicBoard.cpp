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
    for(int y = 0; y < board.m_squareLayer.size(); y++){
        std::vector<int> squareRow;
        std::vector<std::unique_ptr<int>> highlightRow;
        for(int x = 0; x < board.m_squareLayer.at(y).size(); x++){
            squareRow.push_back(board.m_squareLayer.at(y).at(x));
            std::unique_ptr<int> noHighlight;
            highlightRow.push_back(std::move(noHighlight));
        }
        m_squareLayer.push_back(squareRow);
        m_squareHighlight.push_back(std::move(highlightRow));
    }
}

LogicBoard::~LogicBoard(){}

bool LogicBoard::init(const BoardDataContainer& data){
    m_repeatedSquareIds = data.repeatedSquareIds;

    if(m_repeatedSquareIds.size() == 0){
        std::cout << "Failed to setup LogicBoard: repeatSquares not set" << std::endl;
        return false;
    }

    for(unsigned int y = 0; y < data.rows; y++){
        std::vector<int> squareRow;
        for(unsigned int x = 0; x < data.columns; x++){
            squareRow.push_back(m_repeatedSquareIds.at((x+y)%m_repeatedSquareIds.size()));
        }
        m_squareLayer.push_back(squareRow);
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

    for(int y = 0; y < m_squareLayer.size(); y++){
        std::vector<std::unique_ptr<int>> highlightRow;
        for(int x = 0; x < m_squareLayer.at(y).size(); x++){
            std::unique_ptr<int> noHighlight;
            highlightRow.push_back(std::move(noHighlight));
        }
        m_squareHighlight.push_back(std::move(highlightRow));
    }

    return true;
}

const unsigned int LogicBoard::width() const{
    return m_squareLayer.at(0).size();
}

const unsigned int LogicBoard::height() const{
    return m_squareLayer.size();
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

bool LogicBoard::isEmptySquare(const Coord& coord) const{
    if(!isWithinBoard(coord)){
        return false;
    }
    return m_pieceLayer.getEntityAt(coord) == std::nullopt;
}

std::optional<int> LogicBoard::getSquareColorAt(const Coord& coord) const{
    if(!isWithinBoard(coord)){
        return std::nullopt;
    }

    return m_squareLayer.at(coord.y).at(coord.x);
}

std::optional<LogicEntity> LogicBoard::getEntityAt(const Coord& coord) const{
    return m_pieceLayer.getEntityAt(coord);
}

std::optional<LogicArrow> LogicBoard::getArrowAt(const CoordPair& coordPair) const{
    auto it = m_arrows.find(coordPair);

    if(it == m_arrows.end()){
        return std::nullopt;
    }

    return it->second;
}

std::optional<int> LogicBoard::getSquareHighlightAt(const Coord& coord) const{

    std::cout << "LogicBoard: getSquareHighlightAt" << std::endl;
    if(coord.x > m_squareHighlight.at(0).size()){
        return std::nullopt;
    }
    if(coord.y > m_squareHighlight.size()){
        return std::nullopt;
    }

    if(!m_squareHighlight.at(coord.y).at(coord.x)){
        return std::nullopt;
    }

    int colorId = *m_squareHighlight[coord.y][coord.x];
    return colorId;
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
        std::cout << "The square is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.getEntityAt(coord) != std::nullopt){
        std::cout << "LogicBoard: Unable to add entity at " << coord.getNotation() << std::endl;
        std::cout << "The square is already occupied" << std::endl;
        return false;
    }

    m_pieceLayer.addEntity(coord,entity);
    return true;
}

bool LogicBoard::removeEntity(const Coord& coord){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to remove entity at " << coord.getNotation() << std::endl;
        std::cout << "The square is outside of the board" << std::endl;
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
        std::cout << "start square is out of bounds" << std::endl;
        return false;
    }

    if(!isWithinBoard(toCoord)){
        std::cout << "LogicBoard: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cout << "destination square is out of bounds" << std::endl;
        return false;
    }

    if(isEmptySquare(fromCoord)){
        std::cout << "LogicBoard: Unable to move entity from " << fromCoord.getNotation() << std::endl;
        std::cout << "No piece is standing there" << std::endl;
        return false;
    }

    if(!isEmptySquare(toCoord)){
        m_pieceLayer.removeEntity(toCoord);
    }

    m_pieceLayer.moveEntity(fromCoord, toCoord);
    return true;
}

bool LogicBoard::addSquareHighlight(const Coord& coord, const int colorId){
    
    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to add square highlight." << std::endl;
        std::cout << "Coord is not a valid square (value:" << coord.getNotation() << ")" << std::endl;
        return false;
    }

    if(colorId < 0){
        std::cout << "LogicBoard: Unable to add square highlight." << std::endl;
        std::cout << "ColorId is not set (value: " << colorId << ")" << std::endl;
        return false;
    }

    if(!m_squareHighlight.at(coord.y).at(coord.x)){
        m_squareHighlight.at(coord.y).at(coord.x) = std::make_unique<int>(colorId);
        return true;
    }

    if(*m_squareHighlight.at(coord.y).at(coord.x) == colorId){
        m_squareHighlight.at(coord.y).at(coord.x) = nullptr;
        return true;
    }

    *m_squareHighlight.at(coord.y).at(coord.x) = colorId;
    return true;
}

bool LogicBoard::addArrow(const CoordPair& coordPair, const LogicArrow& arrow){

    if(!isWithinBoard(coordPair.from)){
        std::cout << "LogicBoard: Unable to add arrow from square: " << coordPair.from.getNotation() << std::endl;
        std::cout << "Starting square is outside of the board" << std::endl;
        return false;
    }

    if(!isWithinBoard(coordPair.to)){
        std::cout << "LogicBoard: Unable to add arrow to square: " << coordPair.to.getNotation() << std::endl;
        std::cout << "Destination square is outside of the board" << std::endl;
        return false;
    }

    if(arrow.getColorId() < 0){
        std::cout << "LogicBoard: Unable to add arrow" << std::endl;
        std::cout << "ColorId is not set (value: " << arrow.getColorId() << ")" << std::endl;
        return false;
    }

    auto it = m_arrows.find(coordPair);

    if(it != m_arrows.end()){
        std::cout << "LogicBoard: Unable to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "There is already an arrow there" << std::endl;
        return false;
    }

    m_arrows.insert({coordPair, arrow});
    return true;
}


bool LogicBoard::removeArrow(const CoordPair& coordPair){

    auto it = m_arrows.find(coordPair);
    if(it == m_arrows.end()){
        std::cout << "LogicBoard: Unable to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cout << "There is no arrow there" << std::endl;
        return false;
    }

    m_arrows.erase(it);
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
    out << "RepeatSquares:";
    for(const auto& id: board.m_repeatedSquareIds){
        out << " " << id;
    }
    out << board.m_pieceLayer;
    return out;
}
