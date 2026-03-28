#include "Board.h"

#include <iostream>
#include <fstream>
#include <cctype> //isdigit

#include "../Entity/Shape/Circle/LogicCircle.h"

using namespace sigrid;

Board::Board(){}

void Board::init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData, ColorManager* const tileColorManagerPtr, PieceManager* const pieceManagerPtr, ColorManager* const arrowColorManagerPtr){

    m_filename = boardData.filename;

    m_logicBoard = std::make_unique<sigrid::LogicBoard>();

    if(m_logicBoard->init(boardData)){
        m_graphicBoard = std::make_unique<sigrid::GraphicBoard>();
        m_graphicBoard->init(*m_logicBoard, graphicData, pieceManagerPtr, tileColorManagerPtr, arrowColorManagerPtr);
    }
}

Board& Board::operator=(const Board& rhs){
    m_filename = rhs.m_filename;
    m_imageFilename = rhs.m_imageFilename;
    if(rhs.m_logicBoard){
        if(!m_logicBoard){
            m_logicBoard = std::make_unique<LogicBoard>();
        }
        *m_logicBoard = *(rhs.m_logicBoard);
    }
    
    if(rhs.m_graphicBoard){
        if(!m_graphicBoard){
            m_graphicBoard = std::make_unique<GraphicBoard>();
        }
        *m_graphicBoard = *(rhs.m_graphicBoard);
    }
    
    if(rhs.m_selection){
        if(!m_selection){
            m_selection = std::make_unique<Coord>();
        }
        *m_selection = *(rhs.m_selection);
    }

    return *this;
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

std::string Board::getName() const{
    return m_filename;
}

std::string Board::getImageName() const{
    return m_imageFilename;
}

bool Board::contains(sf::Vector2i point) const{
    return m_graphicBoard->contains(point);
}

bool Board::isEmptyTile(const Coord& coord) const{
    return m_logicBoard->isEmptyTile(coord);
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

std::optional<Coord> Board::getTileCoord(sf::Vector2i point){
    return m_graphicBoard->getTileCoord(point);
}

std::optional<LogicEntity> Board::getLogicEntity(const Coord& coord){
    auto entity_o = m_logicBoard->getEntityAt(coord);
    if(entity_o == std::nullopt){
        return std::nullopt;
    }
    return entity_o.value();
}

std::optional<GraphicEntity> Board::getGraphicEntity(const Coord& coord){
    auto entity_o = m_graphicBoard->getEntityAt(coord);
    if(entity_o == std::nullopt){
        return std::nullopt;
    }
    return entity_o.value();
}

std::optional<LogicTile> Board::getTile(const Coord& coord){
    auto tile_o = m_logicBoard->getTile(coord);
    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    return tile_o.value();
}

std::optional<LogicArrow> Board::getLogicArrow(const CoordPair& coordPair){
    auto arrow_o = m_logicBoard->getArrowAt(coordPair);
    if(arrow_o == std::nullopt){
        return std::nullopt;
    }
    return arrow_o.value();
}

std::string Board::getFen() const{
    return m_logicBoard->getFen();
}

void Board::select(const Coord& newCoord){
    if(!m_selection){
        m_selection = std::make_unique<Coord>(newCoord);
        m_graphicBoard->highlightTile(newCoord);
        return;
    }

    Coord oldCoord = *m_selection;
    
    if(oldCoord == newCoord){
        m_selection = nullptr;
        m_graphicBoard->unhighlight();
        return;
    }

    if(m_logicBoard->isEmptyTile(oldCoord)){
        m_selection = std::make_unique<Coord>(newCoord);
        m_graphicBoard->highlightTile(newCoord);
        return;
    }

    if(m_logicBoard->moveEntity(oldCoord, newCoord)){
        m_graphicBoard->moveEntity(oldCoord, newCoord);
    }

    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::deselect(){
    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::addEntity(const Coord& coord, const LogicEntity& newEntity){

    if(!m_logicBoard->isWithinBoard(coord)){
        std::cout << "Board: Failed to add Entity at " << coord.getNotation() << std::endl;
        std::cout << "because it is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_logicBoard->getEntityAt(coord);

    if(occupyingEntity_o != std::nullopt){
        std::cout << "Board: Failed to add Entity at " << coord.getNotation() << std::endl;
        std::cout << "because the tile is already occupied" << std::endl;
        return;
    }

    if(m_logicBoard->addEntity(coord, newEntity)){
        m_graphicBoard->addEntity(coord, newEntity);
    }
}

void Board::removeEntity(const Coord& coord){

    if(!m_logicBoard->isWithinBoard(coord)){
        std::cout << "Board: Failed to remove Entity at " << coord.getNotation() << std::endl;
        std::cout << "because it is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_logicBoard->getEntityAt(coord);

    if(occupyingEntity_o == std::nullopt){
        std::cout << "Board: Failed to remove Entity at " << coord.getNotation() << std::endl;
        std::cout << "because there is no entity there" << std::endl;
        return;
    }

    if(m_logicBoard->removeEntity(coord)){
        m_graphicBoard->removeEntity(coord);
    }
}

void Board::addEntityAtSelection(const LogicEntity& newEntity){
    if(m_selection == nullptr){
        return;
    }
    addEntity(*m_selection, newEntity);
    m_selection = nullptr;
    m_graphicBoard->unhighlight();
}

void Board::addTileHighlight(const Coord& coord, const int& colorId){

    if(!m_logicBoard->isWithinBoard(coord)){
        std::cout << "Board: Failed to add highlight at "
            << coord.getNotation() << std::endl;
        std::cout << "because it is out of bounds" << std::endl;
        return;
    }

    auto tile_o = m_logicBoard->getTile(coord);

    if(tile_o == std::nullopt){
        std::cout << "Board: Failed to add highlight at "
            << coord.getNotation() << std::endl;
        std::cout << "There is no tile there" << std::endl;
        return;
    }

    auto highlightColor_o = tile_o.value().getHighlightColorId();

    if(highlightColor_o != std::nullopt){
        std::cout << "Board: Failed to add highlight at "
            << coord.getNotation() << std::endl;
        std::cout << "There is already a highlight there" << std::endl;
        return;
    }

    if(m_logicBoard->addTileHighlight(coord, colorId)){
        m_graphicBoard->addTileHighlight(coord, colorId);
    }
}

void Board::removeTileHighlight(const Coord& coord){

    if(!m_logicBoard->isWithinBoard(coord)){
        std::cout << "Board: Failed to remove highlight at "
            << coord.getNotation() << std::endl;
        std::cout << "because it is out of bounds" << std::endl;
        return;
    }

    auto tile_o = m_logicBoard->getTile(coord);

    if(tile_o == std::nullopt){
        std::cout << "Board: Failed to remove highlight at "
            << coord.getNotation() << std::endl;
        std::cout << "There is no tile there" << std::endl;
        return;
    }

    auto highlightColor_o = tile_o.value().getHighlightColorId();

    if(highlightColor_o == std::nullopt){
        std::cout << "Board: Failed to remove highlight at "
            << coord.getNotation() << std::endl;
        std::cout << "There is no highlight there" << std::endl;
        return;
    }

    if(m_logicBoard->removeTileHighlight(coord)){
        m_graphicBoard->removeTileHighlight(coord);
    }
}

void Board::dragAndDrop(const Coord& fromCoord, const Coord& toCoord){
    assert(fromCoord != toCoord);

    if(m_logicBoard->isEmptyTile(fromCoord)){
        return;
    }

    if(m_logicBoard->moveEntity(fromCoord, toCoord)){
        m_graphicBoard->moveEntity(fromCoord, toCoord);
    }
    
}

void Board::addArrow(const Coord& fromCoord, const Coord& toCoord, const LogicArrow& newArrow){

    if(!m_logicBoard->isWithinBoard(fromCoord)){
        std::cout << "Board: Unable to add arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cout << "Starting tile is out of bounds" << std::endl;
        return;
    }

    if(!m_logicBoard->isWithinBoard(toCoord)){
        std::cout << "Board: Unable to add arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cout << "Destination tile is out of bounds" << std::endl;
        return;
    }

    auto occupyingArrow_o = m_logicBoard->getArrowAt({fromCoord, toCoord});

    if(occupyingArrow_o != std::nullopt){
        std::cout << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cout << "There is already an arrow there" << std::endl;
        return;
    }

    if(m_logicBoard->addArrow({fromCoord, toCoord}, newArrow)){
        m_graphicBoard->addArrow({fromCoord, toCoord}, newArrow);
    }
}

void Board::removeArrow(const Coord& fromCoord, const Coord& toCoord){

    if(!m_logicBoard->isWithinBoard(fromCoord)){
        std::cout << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cout << "Starting tile is out of bounds" << std::endl;
        return;
    }

    if(!m_logicBoard->isWithinBoard(toCoord)){
        std::cout << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cout << "Destination tile is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_logicBoard->getArrowAt({fromCoord, toCoord});

    if(occupyingEntity_o == std::nullopt){
        std::cout << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cout << "There is no arrow there" << std::endl;
        return;
    }

    if(m_logicBoard->removeArrow({fromCoord, toCoord})){
        m_graphicBoard->removeArrow({fromCoord, toCoord});
    }
}

void Board::updateDragArrow(const Coord& fromCoord, const Coord& toCoord, const int& colorId){
    m_graphicBoard->updateDragArrow(fromCoord, toCoord, colorId);
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

            addEntity({x,y}, logicPiece);
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