#include "LogicBoard.h"

#include <iostream>
#include "../Piece/LogicPiece.h"
#include <cctype>

#include <algorithm>

#include <fstream>

using namespace sigrid;

LogicBoard::LogicBoard(const int columns, const int rows, const std::vector<int>& repeatSquares, const std::vector<PieceDataContainer> pieces)
: m_repeatSquareIds{repeatSquares}{

    if(repeatSquares.size() == 0){
        std::cout << "Failed to setup LogicBoard: repeatSquares not set" << std::endl;
        return;
    }

    for(unsigned int y = 0; y < rows; y++){
        std::vector<int> squareRow;
        for(unsigned int x = 0; x < columns; x++){
            squareRow.push_back(repeatSquares.at((x+y)%repeatSquares.size()));
        }
        m_squareLayer.push_back(squareRow);
    }

    for(const auto pieceContainer : pieces){

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
        m_pieces.insert({coord, LogicPiece(pieceContainer.name, pieceContainer.colorId)});
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
: m_pieces{board.m_pieces}{
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
    return m_pieces.find(coord) == m_pieces.end();
}

std::optional<int> LogicBoard::getSquareColorAt(const Coord& coord) const{
    if(!isWithinBoard(coord)){
        return std::nullopt;
    }

    return m_squareLayer.at(coord.y).at(coord.x);
}

std::optional<LogicPiece> LogicBoard::getPieceAt(const Coord& coord) const{
    
    auto it = m_pieces.find(coord);
    if(it == m_pieces.end()){
        return std::nullopt;
    }
    return it->second;
}

std::optional<LogicCircle> LogicBoard::getCircleAt(const Coord& coord) const{
    auto it = m_circles.find(coord);
    if(it == m_circles.end()){
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
            auto it = m_pieces.find({x,y});
            if(it == m_pieces.end()){
                i++;
            }
            else{
                if(i > 0){
                    fen.append(std::to_string(i));;
                    i = 0;
                }
                std::string s = it->second.notation();
                if(it->second.colorId() == 1){
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

void LogicBoard::addPiece(const LogicPiece& piece, const Coord& coord){
    
    auto it = m_pieces.find(coord);

    if(it == m_pieces.end()){
        m_pieces.insert({coord, piece});
        return;
    }

    if(it->second == piece){
        m_pieces.erase(it);
        return;
    }

    it->second = piece;
}

void LogicBoard::removePiece(const Coord& coord){
    auto it = m_pieces.find(coord);

    if(it == m_pieces.end()){
        std::cout << "LogicBoard: Unable to remove piece at " << coord.getNotation() << std::endl;
        std::cout << "There is no piece there";
        return;
    }

    m_pieces.erase(it);
}

bool LogicBoard::movePiece(const Coord& fromCoord, const Coord& toCoord){

    if(fromCoord.x == toCoord.x && fromCoord.y == toCoord.y){
        std::cout << "LogicBoard: Unable to move piece from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cout << "both coordinates are the same" << std::endl;
        return false;
    }

    auto itFrom = m_pieces.find(fromCoord);

    if(itFrom == m_pieces.end()){
        std::cout << "LogicBoard: Unable to move piece from " << fromCoord.getNotation() << std::endl;
        std::cout << "No piece is standing there" << std::endl;
        return false;
    }

    auto itTo = m_pieces.find(toCoord);

    if(itTo != m_pieces.end()){
        m_pieces.erase(itTo);
    }

    addPiece(itFrom->second, toCoord);
    removePiece(fromCoord);
    return true;
}

void LogicBoard::addSquareHighlight(const int colorId, const Coord& coord){
    assert(coord.x < m_squareLayer.at(0).size());
    assert(coord.y < m_squareLayer.size());

    if(!m_squareHighlight.at(coord.y).at(coord.x)){
        m_squareHighlight.at(coord.y).at(coord.x) = std::make_unique<int>(colorId);
        return;
    }

    if(*m_squareHighlight.at(coord.y).at(coord.x) == colorId){
        m_squareHighlight.at(coord.y).at(coord.x) = nullptr;
        return;
    }

    *m_squareHighlight.at(coord.y).at(coord.x) = colorId;
}

void LogicBoard::addArrow(const LogicArrow& arrow){

    for(auto it = m_arrows.begin(); it != m_arrows.end(); it++){
        if(it->fromCoord() == arrow.fromCoord() && it->toCoord() == arrow.toCoord()){
            if(it->colorId() == arrow.colorId()){
                m_arrows.erase(it);
                return;
            }
            it->setColor(arrow.colorId());
            return;
        }
    }
    m_arrows.push_back(arrow);
}


void LogicBoard::removeArrow(const LogicArrow& arrow){
    auto it = std::find(m_arrows.begin(), m_arrows.end(), arrow);
    if(it != m_arrows.end()){
        m_arrows.erase(it);
    }
}

void LogicBoard::addCircle(const LogicCircle& circle, const Coord& coord){

    auto it = m_circles.find(coord);
    if(it != m_circles.end()){
        std::cout << "Unable to add circle at " << coord.getNotation() << std::endl;
        std::cout << "There is already a circle there" << std::endl;
        return;
    }

    m_circles.insert({coord, circle});
}

void LogicBoard::removeCircle(const Coord& coord){
    auto it = m_circles.find(coord);
    if(it == m_circles.end()){
        std::cout << "Unable to remove circle at " << coord.getNotation() << std::endl;
        std::cout << "There is no circle there" << std::endl;
        return;
    }

    m_circles.erase(coord);
}

void LogicBoard::setCircleColorAt(const int colorId, const Coord& coord){

    auto it = m_circles.find(coord);
    if(it == m_circles.end()){
        std::cout << "Unable to set circle color at " << coord.getNotation() << std::endl;
        std::cout << "There is no circle there" << std::endl;
        return;
    }

    m_circles.at(coord).setColor(colorId);
}

void LogicBoard::print(){
    std::cout << "Printing board" << std::endl;
    std::cout << "height = " << height() << std::endl;
    std::cout << "width = " << width() << std::endl;
    
    for(int y = 0; y < height(); y++){
        for(int x = 0; x < width(); x++){
            auto it = m_pieces.find({x,y});
            if(it == m_pieces.end()){
                std::cout << " ";
            }
            else{
                std::cout << it->second.notation();
            }
        }
        std::cout << "\n";
    }
}

void LogicBoard::clear(){
    for(int y = 0; y < height(); y++){
        for(int x = 0; x < width(); x++){
            auto it = m_pieces.find({x,y});
            if(it != m_pieces.end()){
                m_pieces.erase(it);
            }
        }
    }
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicBoard &board)
{
    out << "Columns: " << board.width() << "\n";
    out << "Rows: " << board.height() << "\n";
    out << "RepeatSquares:";
    for(const auto& id: board.m_repeatSquareIds){
        out << " " << id;
    }
    out << "\n";
    for(int y = board.m_squareLayer.size()-1; y >= 0; y--){
        for(int x = 0; x < board.m_squareLayer.at(0).size(); x++){
            auto it = board.m_pieces.find({x,y});
            if(it == board.m_pieces.end()){
                continue;
            }

            out << "\n";

            out << "Piece: " << it->second.colorId() << " " << it->second.notation() << " " << it->first.getNotation();
        }
    }
    return out;
}
