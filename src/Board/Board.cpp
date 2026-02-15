#include "Board.h"

#include <iostream>
#include <fstream>
#include <cctype> //isdigit

#include "LogicBoardContainer.h"

using namespace sigrid;

Board::Board(std::string boardFilename, const GraphicBoardConfigContainer& graphicData, const std::vector<uint32_t>& squareColors, PieceManager* pieceManagerPtr, ColorManager* colorManagerPtr)
: m_pieceManagerPtr(pieceManagerPtr){

    LogicBoardContainer boardContainer;

    std::ifstream ifs(boardFilename);

    if(!ifs.is_open()){
        std::cout << "LogicBoard: Failed to open position from file: " << boardFilename << std::endl;
        return;
    }

    std::string key;
    while(ifs >> key){

        if(key == "Columns:"){
            ifs >> boardContainer.columns;
        }
        else if(key == "Rows:"){
            ifs >> boardContainer.rows;
        }
        else if(key == "RepeatSquares:"){
            int squareId;
            ifs >> squareId;
            boardContainer.repeatedSquareIds.push_back(squareId);
            ifs >> squareId;
            boardContainer.repeatedSquareIds.push_back(squareId);
        }
        else if(key == "Piece:"){
            sigrid::LogicPieceContainer pieceContainer;
            ifs >> pieceContainer.colorId;
            ifs >> pieceContainer.name;
            ifs >> pieceContainer.position;
            boardContainer.logicPieces.push_back(pieceContainer);
        }
    }

    m_logicBoard = std::make_unique<sigrid::LogicBoard>(boardContainer.columns, boardContainer.rows, boardContainer.repeatedSquareIds, boardContainer.logicPieces, boardFilename);

    m_graphicBoard = std::make_unique<sigrid::GraphicBoard>(*m_logicBoard, graphicData, pieceManagerPtr, squareColors, colorManagerPtr);

}

void Board::setPosition(sf::Vector2f position){
    m_graphicBoard->setPosition(position);
}

void Board::setPositionX(const float x){
    m_graphicBoard->setPositionX(x);
}

void Board::setScale(const float scale){
    m_graphicBoard->setScale(scale);
}

unsigned int Board::getNumColumns() const{
    return m_logicBoard->width();
}

unsigned int Board::getImageWidth() const{
    return m_graphicBoard->getImageWidth();
}

unsigned int Board::getImageHeight() const{
    return m_graphicBoard->getImageHeight();
}

float Board::getDisplayWidth() const{
    return m_graphicBoard->getDisplayWidth();
}

float Board::getDisplayHeight() const{
    return m_graphicBoard->getDisplayHeight();
}

bool Board::contains(sf::Vector2i point) const{
    return m_graphicBoard->contains(point);
}

bool Board::isEmptySquare(const Coord& coord) const{
    return m_logicBoard->isEmptySquare(coord);
}

bool Board::isCoordinatesOutside() const{
    return m_graphicBoard->isCoordinatesOutside();
}

bool Board::isWithinPlayerToMoveToken(sf::Vector2i point) const{
    return m_graphicBoard->isWithinPlayerToMoveToken(point);
}

std::optional<Coord> Board::getSquareCoord(sf::Vector2i point){
    return m_graphicBoard->getSquareCoord(point);
}

std::optional<Piece> Board::getPiece(const Coord& coord){
    auto piece_o = m_logicBoard->getPieceAt(coord);
    if(piece_o == std::nullopt){
        return std::nullopt;
    }
    return m_pieceManagerPtr->getPiece(*piece_o.value());
}

void Board::select(const Coord& newCoord){
    if(!m_selection){
        m_selection = std::make_unique<Coord>(newCoord);
        m_graphicBoard->highlightSquare(newCoord);
        return;
    }

    Coord oldCoord = *m_selection;
    
    if(oldCoord == newCoord){
        m_selection = nullptr;
        m_graphicBoard->unhighlight();
        return;
    }

    std::optional<sigrid::LogicPiece*> o_piece = m_logicBoard->getPieceAt(oldCoord);

    if(o_piece == std::nullopt){
        m_selection = std::make_unique<Coord>(newCoord);
        m_graphicBoard->highlightSquare(newCoord);
        return;
    }

    movePiece(oldCoord, newCoord);
    

    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::keyPressed(sf::Event::KeyPressed event){

}

void Board::textEntered(std::string text){
    int colorId;
    if(std::isupper(text.back())){
        colorId = 0;
    }
    else{
        colorId = 1;
    }

    LogicPiece logicPiece{text, colorId};

    auto piece_o = m_pieceManagerPtr->getPiece(logicPiece);

    if(piece_o == std::nullopt){
        return;
    }
    if(m_selection == nullptr){
        return;
    }
    addPiece(piece_o.value(), *m_selection);
    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::deselect(){
    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::addPiece(const Piece& piece, const Coord& coord){

    auto logicPiecePtr_o = m_logicBoard->getPieceAt(coord);
    if(logicPiecePtr_o == std::nullopt){
        m_logicBoard->addPiece(piece.logic(), coord);
        m_graphicBoard->addPiece(piece.graphic(), coord);
        return;
    }

    if(*(logicPiecePtr_o.value()) == piece.logic()){
        m_logicBoard->removePiece(coord);
        m_graphicBoard->removePiece(coord);
        return;
    }

    m_logicBoard->removePiece(coord);
    m_graphicBoard->removePiece(coord);
    m_logicBoard->addPiece(piece.logic(), coord);
    m_graphicBoard->addPiece(piece.graphic(), coord);
}

void Board::addSquareHighlight(const int colorId, const Coord& coord){

    m_logicBoard->addSquareHighlight(colorId, coord);
    m_graphicBoard->addSquareHighlight(colorId, coord);

}

void Board::movePiece(const Coord& fromCoord, const Coord& toCoord){
    assert(fromCoord != toCoord);

    if(m_logicBoard->movePiece(fromCoord, toCoord)){
        m_graphicBoard->movePiece(fromCoord, toCoord);
    }
    
}

void Board::addArrow(const int colorId, const Coord& fromCoord, const Coord& toCoord){
    LogicArrow logicArrow{fromCoord, toCoord, colorId};
    m_logicBoard->addArrow(logicArrow);
    m_graphicBoard->addArrow(logicArrow);
}

void Board::updateDragArrow(const Coord& fromCoord, const Coord& toCoord){
    m_graphicBoard->updateDragArrow(fromCoord, toCoord);
}

void Board::removeDragArrow(){
    m_graphicBoard->removeDragArrow();
}

void Board::loadFENPiecePlacement(std::string fenPiecePlacement){

    int x = 0;
    int y = 0;
    for(int i = 0; i < fenPiecePlacement.size(); i++){
        std::string s = fenPiecePlacement.substr(i, 1);
        if(std::isdigit(s.at(0))){
            x+= std::stoi(s);
        }
        else if(s == "/"){
            x = 0;
            y++;
        }
        else{
            int colorId;
            if(std::isupper(s.back())){
                colorId = 0;
            }
            else{
                colorId = 1;
            }
            s.at(0) = std::toupper(s.at(0));
            LogicPiece logicPiece{s, colorId};

            auto piece_o = m_pieceManagerPtr->getPiece(logicPiece);
            if(piece_o != std::nullopt){
                addPiece(piece_o.value(), {x,y});
            }
            else{
                std::cout << "Failed to get piece of character \"" << s
                << "\" when loading FEN" << std::endl;
            }
            x++;
        }
    }
}

void Board::saveLogic(){
    m_logicBoard->save();
}

void Board::saveImage(const std::string& filename){
    m_graphicBoard->saveImage(filename);
}

void Board::clear(){
    m_logicBoard->clear();
    m_graphicBoard->clear();
}

void Board::print(){
    m_logicBoard->print();
}

void Board::addCoordinates(){
    m_graphicBoard->addCoordinates();
}

void Board::removeCoordinates(){
    m_graphicBoard->removeCoordinates();
}

void Board::moveCoordinatesOutside(){
    m_graphicBoard->moveCoordinatesOutside();
}

void Board::moveCoordinatesInside(){
    m_graphicBoard->moveCoordinatesInside();
}

void Board::setBigCoordinates(){
    m_graphicBoard->setBigCoordinates();
}

void Board::setSmallCoordinates(){
    m_graphicBoard->setSmallCoordinates();
}

void Board::addBorder(){
    m_graphicBoard->addBorder();
}

void Board::removeBorder(){
    m_graphicBoard->removeBorder();
}

void Board::addPlayerToMoveToken(){
    m_graphicBoard->addPlayerToMoveToken();
}

void Board::removePlayerToMoveToken(){
    m_graphicBoard->removePlayerToMoveToken();
}

void Board::togglePlayerToMoveToken(){
    m_graphicBoard->togglePlayerToMoveToken();
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*m_graphicBoard);
}