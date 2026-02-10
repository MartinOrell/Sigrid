#include "LogicBoard.h"

#include <iostream>
#include "../Piece/LogicPiece.h"
#include <cctype>

#include <algorithm>

#include <fstream>

using namespace sigrid;

LogicBoard::LogicBoard(const std::string& filename){

    std::ifstream ifs(filename);

    if(!ifs.is_open()){
        std::cout << "LogicBoard: Failed to open position from file: " << filename << std::endl;
        return;
    }

    unsigned int columns;
    unsigned int rows;

    std::string key;
    while(ifs >> key){

        if(key == "Columns:"){
            ifs >> columns;
        }
        else if(key == "Rows:"){
            ifs >> rows;
        }
        else if(key == "RepeatSquares:"){
            int tmp;
            ifs >> tmp;
            ifs >> tmp;
            if(rows < 1){
                std::cout << "LogicBoard: Rows not set" << std::endl;
                return;
            }
            if(columns < 1){
                std::cout << "LogicBoard: Columns not set" << std::endl;
                return;
            }
            for(unsigned int y = 0; y < rows; y++){
                std::vector<int> squareRow;
                std::vector<LogicPiece*> pieceRow;
                for(unsigned int x = 0; x < columns; x++){
                    squareRow.push_back((x+y)%2);
                    pieceRow.push_back(nullptr);
                }
                m_squareLayer.push_back(squareRow);
                m_pieceLayer.push_back(pieceRow);
            }
        }
        else if(key == "Piece:"){
            int colorId;
            ifs >> colorId;
            std::string notation;
            ifs >> notation;

            std::string coordName;
            ifs >> coordName;
            int x = coordName.at(0) - 'a';
            int y = rows - (coordName.at(1) - '1') - 1;

            if(y < 0){
                std::cout << "Failed to set piece at " << coordName << ", missing row on board" << std::endl;
                continue;
            }
            if(y >= m_pieceLayer.size()){
                std::cout << "Failed to set piece at " << coordName << ", missing row on board" << std::endl;
                continue;
            }
            if(x < 0){
                std::cout << "Failed to set piece at " << coordName << ", missing column on board" << std::endl;
                continue;
            }
            if(x >= m_pieceLayer.at(y).size()){
                std::cout << "Failed to set piece at " << coordName << ", missing column on board" << std::endl;
                continue;
            }
            m_pieceLayer.at(y).at(x) = new LogicPiece(notation, colorId);
        }
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

LogicBoard::LogicBoard(const LogicBoard& board){
    for(int y = 0; y < board.m_squareLayer.size(); y++){
        std::vector<int> squareRow;
        std::vector<LogicPiece*> pieceRow;
        std::vector<std::unique_ptr<int>> highlightRow;
        for(int x = 0; x < board.m_squareLayer.at(y).size(); x++){
            squareRow.push_back(board.m_squareLayer.at(y).at(x));
            pieceRow.push_back(board.m_pieceLayer.at(y).at(x));
            std::unique_ptr<int> noHighlight;
            highlightRow.push_back(std::move(noHighlight));
        }
        m_squareLayer.push_back(squareRow);
        m_pieceLayer.push_back(pieceRow);
        m_squareHighlight.push_back(std::move(highlightRow));
    }
}

/*
LogicBoard::LogicBoard(const std::string& fen){
    int x = 0;
    int y = 0;
    std::vector<int> squareRow;
    std::vector<LogicPiece*> pieceRow;
    for(int i = 0; i < fen.size(); i++){
        std::string s = fen.substr(i, 1);
        if(std::isdigit(s.at(0))){
            for(int j = 0; j < std::stoi(s); j++){
                squareRow.push_back((x+y)%2);
                pieceRow.push_back(nullptr);
                x++;
            }
            x+= std::stoi(s);
        }
        else if(s == "/"){
            x = 0;
            y++;
            m_squareLayer.push_back(squareRow);
            squareRow.clear();
            m_pieceLayer.push_back(pieceRow);
            pieceRow.clear();
        }
        else{
            int colorId;
            if(isupper(s.back())){
                colorId = 0;
            }
            else{
                colorId = 1;
            }
            sigrid::LogicPiece* newPiece = new LogicPiece(s, colorId);
            squareRow.push_back((x+y)%2);
            pieceRow.push_back(newPiece);
            x++;
        }
    }
    m_squareLayer.push_back(squareRow);
    m_pieceLayer.push_back(pieceRow);


    for(int y1 = 0; y1 < m_squareLayer.size(); y1++){
        std::vector<std::unique_ptr<int>> highlightRow;
        for(int x1 = 0; x1 < m_squareLayer.at(y1).size(); x1++){
            std::unique_ptr<int> noHighlight;
            highlightRow.push_back(std::move(noHighlight));
        }
        m_squareHighlight.push_back(std::move(highlightRow));
    }
}
*/

LogicBoard::~LogicBoard(){
    for(int y = 0; y < height(); y++){
        for(int x = 0; x < width(); x++){
            if(m_pieceLayer[y][x] != nullptr){
                delete m_pieceLayer[y][x];
            }
        }
    }
}

const unsigned int LogicBoard::width() const{
    return m_squareLayer.at(0).size();
}

const unsigned int LogicBoard::height() const{
    return m_squareLayer.size();
}

bool LogicBoard::isEmptySquare(const Coord& coord) const{
    if(coord.x >= width()){
        return false;
    }
    if(coord.y >= height()){
        return false;
    }
    return m_pieceLayer[coord.y][coord.x] == nullptr;
}

std::optional<LogicPiece*> LogicBoard::getPieceAt(const Coord& coord) const{
    if(coord.x > m_pieceLayer.at(0).size()){
        return std::nullopt;
    }
    if(coord.y > m_pieceLayer.size()){
        return std::nullopt;
    }
    LogicPiece* piece = m_pieceLayer[coord.y][coord.x];
    if(piece == nullptr){
        return std::nullopt;
    }
    
    int colorId = m_pieceLayer[coord.y][coord.x]->colorId();
    std::string notation = m_pieceLayer[coord.y][coord.x]->notation();

    LogicPiece* returnPiece = new LogicPiece(notation, colorId);

    return returnPiece;
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

void LogicBoard::addPiece(const LogicPiece& piece, const Coord& coord){
    
    if(m_pieceLayer[coord.y][coord.x] == nullptr){
        LogicPiece* newPiece = new LogicPiece{piece};
        m_pieceLayer[coord.y][coord.x] = newPiece;
        return;
    }

    if(*m_pieceLayer[coord.y][coord.x] == piece){
        delete m_pieceLayer[coord.y][coord.x];
        m_pieceLayer[coord.y][coord.x] = nullptr;
        return;
    }

    delete m_pieceLayer[coord.y][coord.x];
    LogicPiece* newPiece = new LogicPiece{piece};
    m_pieceLayer[coord.y][coord.x] = newPiece;
}

void LogicBoard::removePiece(const Coord& coord){
    delete m_pieceLayer[coord.y][coord.x];
    m_pieceLayer[coord.y][coord.x] = nullptr;
}

bool LogicBoard::movePiece(const Coord& fromCoord, const Coord& toCoord){
    assert(fromCoord.x != toCoord.x || fromCoord.y != toCoord.y);

    if(m_pieceLayer[fromCoord.y][fromCoord.x] == nullptr){
        return false;
    }

    if(m_pieceLayer[toCoord.y][toCoord.x] != nullptr){
        delete m_pieceLayer[toCoord.y][toCoord.x];
    } 
    m_pieceLayer[toCoord.y][toCoord.x] = m_pieceLayer[fromCoord.y][fromCoord.x];
    m_pieceLayer[fromCoord.y][fromCoord.x] = nullptr;
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

void LogicBoard::print(){
    std::cout << "Printing board" << std::endl;
    std::cout << "height = " << height() << std::endl;
    std::cout << "width = " << width() << std::endl;
    
    for(int y = 0; y < height(); y++){
        for(int x = 0; x < width(); x++){
            if(m_pieceLayer[y][x] == nullptr){
                std::cout << " ";
            }
            else{
                std::cout << m_pieceLayer[y][x]->notation();
            }
        }
        std::cout << "\n";
    }
}

void LogicBoard::clear(){
    for(int y = 0; y < height(); y++){
        for(int x = 0; x < width(); x++){
            if(m_pieceLayer[y][x] != nullptr){
                delete(m_pieceLayer[y][x]);
                m_pieceLayer[y][x] = nullptr;
            }
        }
    }
}

void LogicBoard::save(const std::string& filename){

    std::cerr << "Saving " << filename << std::endl;

    std::ofstream out(filename);

    std::cerr << "1" << std::endl;

    out << "Columns: " << width() << "\n";
    out << "Rows: " << height() << "\n";
    out << "RepeatSquares: 0 1";
    std::cerr << "3" << std::endl;
    for(int y = m_pieceLayer.size()-1; y >= 0; y--){
        for(int x = 0; x < m_pieceLayer.at(0).size(); x++){

            std::cerr << "[" << x << ", " << y << "]" << std::endl;
            if(m_pieceLayer[y][x] == nullptr){
                continue;
            }
            std::string coord("");
            coord.push_back('a' + x);
            coord.push_back('0' - y + width());
            int colorId = m_pieceLayer[y][x]->colorId();
            std::string notation = m_pieceLayer[y][x]->notation();

            out << "\n";

            out << "Piece: " << colorId << " " << notation << " " << coord;
        }
    }
    std::cerr << "Saved " << filename << std::endl;
}