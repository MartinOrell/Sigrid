#include "Board.h"

#include <iostream>
#include <fstream>
#include <cctype> //isdigit

#include "../Shape/Circle/LogicCircle.h"

using namespace sigrid;

Board::Board(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData, const std::vector<uint32_t>& squareColors, PieceManager* pieceManagerPtr, ColorManager* colorManagerPtr)
: m_pieceManagerPtr(pieceManagerPtr)
, m_filename{boardData.filename}{

    m_logicBoard = std::make_unique<sigrid::LogicBoard>(boardData);

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

void Board::setFilename(const std::string& filename){
    m_filename = filename;
}

void Board::setImageFilename(const std::string& filename){
    m_imageFilename = filename;
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

bool Board::isImageFilenameSet() const{
    return m_imageFilename.length() > 0;
}

std::optional<Coord> Board::getSquareCoord(sf::Vector2i point){
    return m_graphicBoard->getSquareCoord(point);
}

std::optional<LogicPiece> Board::getLogicPiece(const Coord& coord){
    auto entity_o = m_logicBoard->getEntityAt(coord);
    if(entity_o == std::nullopt){
        return std::nullopt;
    }
    if(!std::holds_alternative<LogicPiece>(entity_o.value())){
        return std::nullopt;
    }
    return std::get<LogicPiece>(entity_o.value());
}

std::optional<GraphicPiece> Board::getGraphicPiece(const Coord& coord){
    auto entity_o = m_logicBoard->getEntityAt(coord);
    if(entity_o == std::nullopt){
        return std::nullopt;
    }
    if(!std::holds_alternative<LogicPiece>(entity_o.value())){
        return std::nullopt;
    }
    return m_pieceManagerPtr->getGraphicPiece(std::get<LogicPiece>(entity_o.value()));
}

std::string Board::getFen() const{
    return m_logicBoard->getFen();
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

    if(m_logicBoard->isEmptySquare(oldCoord)){
        m_selection = std::make_unique<Coord>(newCoord);
        m_graphicBoard->highlightSquare(newCoord);
        return;
    }

    if(m_logicBoard->moveEntity(oldCoord, newCoord)){
        m_graphicBoard->moveEntity(oldCoord, newCoord);
    }

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

    auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(logicPiece);

    if(graphicPiece_o == std::nullopt){
        return;
    }
    if(m_selection == nullptr){
        return;
    }
    addPiece(*m_selection, logicPiece);
    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::deselect(){
    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::addPiece(const Coord& coord, const LogicPiece& logicPiece){

    if(!m_logicBoard->isWithinBoard(coord)){
        std::cout << "Board: Failed to add Piece at " << coord.getNotation() << std::endl;
        std::cout << "because it is out of bounds" << std::endl;
        return;
    }

    auto logicEntity_o = m_logicBoard->getEntityAt(coord);

    if(logicEntity_o == std::nullopt){
        if(m_logicBoard->addEntity(coord, logicPiece)){
            m_graphicBoard->addPiece(coord, logicPiece);
        }
        return;
    }

    if(!std::holds_alternative<LogicPiece>(logicEntity_o.value())
    || std::get<LogicPiece>(logicEntity_o.value()) != logicPiece){
        if(m_logicBoard->removeEntity(coord)){
            m_graphicBoard->removeEntity(coord);
        }
        if(m_logicBoard->addEntity(coord, logicPiece)){
            m_graphicBoard->addPiece(coord, logicPiece);
        }
        return;
    }

    if(m_logicBoard->removeEntity(coord)){
        m_graphicBoard->removePiece(coord);
    }
}

void Board::addSquareHighlight(const Coord& coord, const int colorId){

    if(m_logicBoard->addSquareHighlight(coord, colorId)){
        m_graphicBoard->addSquareHighlight(coord, colorId);
    }
}

void Board::dragAndDrop(const Coord& fromCoord, const Coord& toCoord){
    assert(fromCoord != toCoord);

    if(m_logicBoard->isEmptySquare(fromCoord)){
        return;
    }

    if(m_logicBoard->moveEntity(fromCoord, toCoord)){
        m_graphicBoard->moveEntity(fromCoord, toCoord);
    }
    
}

void Board::addArrow(const Coord& fromCoord, const Coord& toCoord, const int colorId){
    LogicArrow logicArrow{fromCoord, toCoord, colorId};
    if(m_logicBoard->addArrow(logicArrow)){
        m_graphicBoard->addArrow(logicArrow);
    }
}

void Board::addCircle(const Coord& coord, const LogicCircle& circle){

    if(!m_logicBoard->isWithinBoard(coord)){
        std::cout << "Board: Failed to add Circle at " << coord.getNotation() << std::endl;
        std::cout << "because it is out of bounds" << std::endl;
        return;
    }

    auto logicEntity_o = m_logicBoard->getEntityAt(coord);

    if(logicEntity_o == std::nullopt){
        if(m_logicBoard->addEntity(coord, circle)){
            m_graphicBoard->addCircle(coord, circle);
        }
        return;
    }

    if(!std::holds_alternative<LogicCircle>(logicEntity_o.value())
    || std::get<LogicCircle>(logicEntity_o.value()) != circle){
        if(m_logicBoard->removeEntity(coord)){
            m_graphicBoard->removeEntity(coord);
        }
        if(m_logicBoard->addEntity(coord, circle)){
            m_graphicBoard->addCircle(coord, circle);
        }
        return;
    }

    if(m_logicBoard->removeEntity(coord)){
        m_graphicBoard->removeCircle(coord);
    }
}

void Board::updateDragArrow(const Coord& fromCoord, const Coord& toCoord){
    m_graphicBoard->updateDragArrow(fromCoord, toCoord);
}

void Board::removeDragArrow(){
    m_graphicBoard->removeDragArrow();
}

void Board::loadFen(const std::string& fen){

    std::cout << "Loading position from FEN: " << fen << std::endl;

    clear();
    int x = 0;
    int y = m_logicBoard->width()-1;
    for(int i = 0; i < fen.size(); i++){
        std::string s = fen.substr(i, 1);
        if(s == " "){
            break;
        }
        else if(std::isdigit(s.at(0))){
            x+= std::stoi(s);
        }
        else if(s == "/"){
            x = 0;
            y--;
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

            auto graphicPiece_o = m_pieceManagerPtr->getGraphicPiece(logicPiece);
            if(graphicPiece_o != std::nullopt){
                addPiece({x,y}, logicPiece);
            }
            else{
                std::cout << "Failed to get piece of character \"" << s
                << "\" when loading FEN" << std::endl;
            }
            x++;
        }
    }
}

bool createFolderForFile(const std::string filename){
    int endPos = filename.find('/',1);
    while(endPos != filename.npos){
        
        std::string folder = filename.substr(0,endPos);

        if(!std::filesystem::exists(folder)){
            bool createFolderIsSuccessful;
            createFolderIsSuccessful = std::filesystem::create_directory(folder);
            if(createFolderIsSuccessful){
                std::cout << "Created folder: " << folder << std::endl;
            }
            else{
                std::cout << "Failed to create folder: " << folder << std::endl;
                return false;
            }
        }

        endPos = filename.find('/',endPos+1);
    }
    return true;
}

void Board::save(){

    if(m_filename.length() == 0){
        std::cout << "Unable to save board, filename is not set" << std::endl;
        return; 
    }

    std::cout << "Saving " << m_filename << std::endl;

    if(!createFolderForFile(m_filename)){
        std::cout << "Saving failed" << std::endl;
        return;
    }

    std::ofstream out(m_filename);

    if(!out.is_open()){
        std::cout << "Failed to open " << m_filename << std::endl;
        std::cout << "Saving failed" << std::endl;
        return;
    }

    out << *m_logicBoard;    

    std::cout << "Saved " << m_filename << std::endl;

    if(m_imageFilename.length() == 0){
        std::cout << "Unable to save board image, filename is not set" << std::endl;
        return;
    }

    out << "\nImageFilename: " << m_imageFilename;

    if(!(createFolderForFile(m_imageFilename))){
        std::cout << "Saving board image failed" << std::endl;
        return;
    }

    m_graphicBoard->saveImage(m_imageFilename);
}

void Board::clear(){
    m_logicBoard->clear();
    m_graphicBoard->clear();
}

void Board::print(){
    m_logicBoard->print();
}

void Board::flipBoard(){
    m_graphicBoard->flip();
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

void Board::setCoordinateSize(const float& size){
    m_graphicBoard->setCoordinateSize(size);
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