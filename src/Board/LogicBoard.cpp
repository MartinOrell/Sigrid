#include "LogicBoard.h"

#include <iostream>
#include "../Piece/LogicPiece.h"
#include <cctype>

#include <algorithm>

#include <fstream>

using namespace sigrid;

LogicBoard::LogicBoard(const BoardDataContainer& data)
: m_repeatedSquareIds{data.repeatedSquareIds}{

    if(m_repeatedSquareIds.size() == 0){
        std::cout << "Failed to setup LogicBoard: repeatSquares not set" << std::endl;
        return;
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
        m_pieceLayer.addPiece(coord, LogicPiece(pieceContainer.name, pieceContainer.colorId));
    }

    for(const auto cData : data.logicCircles){

        Coord coord{cData.position};

        if(!isWithinBoard(coord)){
            std::cout << "LogicBoard constructor: Failed to set circle at " << coord.getNotation() << std::endl;
            std::cout << "coordinate is outside of board" << std::endl;
            continue;
        }

        m_pieceLayer.addCircle(coord, LogicCircle{cData.colorId});
    }

    for(int y = 0; y < m_squareLayer.size(); y++){
        std::vector<std::unique_ptr<int>> highlightRow;
        for(int x = 0; x < m_squareLayer.at(y).size(); x++){
            std::unique_ptr<int> noHighlight;
            highlightRow.push_back(std::move(noHighlight));
        }
        m_squareHighlight.push_back(std::move(highlightRow));
    }
}

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

LogicBoard::~LogicBoard(){
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
    return m_pieceLayer.isEmptySquare(coord);
}

std::optional<int> LogicBoard::getSquareColorAt(const Coord& coord) const{
    if(!isWithinBoard(coord)){
        return std::nullopt;
    }

    return m_squareLayer.at(coord.y).at(coord.x);
}

std::optional<LogicPiece> LogicBoard::getPieceAt(const Coord& coord) const{
    return m_pieceLayer.getPieceAt(coord);
}

std::optional<LogicCircle> LogicBoard::getCircleAt(const Coord& coord) const{
    return m_pieceLayer.getCircleAt(coord);
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
            auto piece_o = m_pieceLayer.getPieceAt({x,y});
            if(piece_o == std::nullopt){
                i++;
            }
            else{
                if(i > 0){
                    fen.append(std::to_string(i));
                    i = 0;
                }
                std::string s = piece_o.value().getNotation();
                if(piece_o.value().getColorId() == 1){
                    s.front() = tolower(s.front());
                }
                fen.append(s);
            }
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

bool LogicBoard::addPiece(const LogicPiece& piece, const Coord& coord){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to add piece at " << coord.getNotation() << std::endl;
        std::cout << "The square is outside of the board" << std::endl;
        return false;
    }

    if(!m_pieceLayer.isEmptySquare(coord)){
        std::cout << "LogicBoard: Unable to add piece at " << coord.getNotation() << std::endl;
        std::cout << "The square is already occupied" << std::endl;
        return false;
    }

    m_pieceLayer.addPiece(coord,piece);
    return true;
}

bool LogicBoard::removePiece(const Coord& coord){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to remove piece at " << coord.getNotation() << std::endl;
        std::cout << "The square is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.isEmptySquare(coord)){
        std::cout << "LogicBoard: Unable to remove piece at " << coord.getNotation() << std::endl;
        std::cout << "There is no piece there" << std::endl;
        return false;
    }

    m_pieceLayer.removePiece(coord);
    return true;
}

bool LogicBoard::movePiece(const Coord& fromCoord, const Coord& toCoord){

    if(fromCoord.x == toCoord.x && fromCoord.y == toCoord.y){
        std::cout << "LogicBoard: Unable to move piece from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cout << "both coordinates are the same" << std::endl;
        return false;
    }

    auto pieceFrom_o = m_pieceLayer.getPieceAt(fromCoord);

    if(pieceFrom_o == std::nullopt){
        std::cout << "LogicBoard: Unable to move piece from " << fromCoord.getNotation() << std::endl;
        std::cout << "No piece is standing there" << std::endl;
        return false;
    }

    auto pieceTo_o = m_pieceLayer.getPieceAt(toCoord);

    if(pieceTo_o != std::nullopt){
        m_pieceLayer.removePiece(toCoord);
    }

    m_pieceLayer.addPiece(toCoord, pieceFrom_o.value());
    m_pieceLayer.removePiece(fromCoord);
    return true;
}

bool LogicBoard::addSquareHighlight(const int colorId, const Coord& coord){
    assert(coord.x < m_squareLayer.at(0).size());
    assert(coord.y < m_squareLayer.size());

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

bool LogicBoard::addArrow(const LogicArrow& arrow){

    for(auto it = m_arrows.begin(); it != m_arrows.end(); it++){
        if(it->fromCoord() == arrow.fromCoord() && it->toCoord() == arrow.toCoord()){
            if(it->colorId() == arrow.colorId()){
                m_arrows.erase(it);
                return true;
            }
            it->setColor(arrow.colorId());
            return true;
        }
    }
    m_arrows.push_back(arrow);
    return true;
}


bool LogicBoard::removeArrow(const LogicArrow& arrow){
    auto it = std::find(m_arrows.begin(), m_arrows.end(), arrow);
    if(it != m_arrows.end()){
        m_arrows.erase(it);
    }
    return true;
}

bool LogicBoard::addCircle(const LogicCircle& circle, const Coord& coord){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to add circle at " << coord.getNotation() << std::endl;
        std::cout << "The square is outside of the board" << std::endl;
        return false;
    }

    if(!m_pieceLayer.isEmptySquare(coord)){
        std::cout << "LogicBoard: Unable to add circle at " << coord.getNotation() << std::endl;
        std::cout << "The square is already occupied" << std::endl;
        return false;
    }

    m_pieceLayer.addCircle(coord,circle);
    return true;
}

bool LogicBoard::removeCircle(const Coord& coord){

    if(!isWithinBoard(coord)){
        std::cout << "LogicBoard: Unable to remove circle at " << coord.getNotation() << std::endl;
        std::cout << "The square is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.isEmptySquare(coord)){
        std::cout << "LogicBoard: Unable to remove circle at " << coord.getNotation() << std::endl;
        std::cout << "There is no circle there" << std::endl;
        return false;
    }

    m_pieceLayer.removeCircle(coord);
    return true;
}

void LogicBoard::print(){
    std::cout << "Printing board" << std::endl;
    std::cout << "height = " << height() << std::endl;
    std::cout << "width = " << width() << std::endl;
    
    for(int y = 0; y < height(); y++){
        for(int x = 0; x < width(); x++){
            auto piece_o = m_pieceLayer.getPieceAt({x,y});
            if(piece_o == std::nullopt){
                std::cout << " ";
            }
            else{
                std::cout << piece_o.value().getNotation();
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
