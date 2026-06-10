#include "Board.h"

#include <iostream>
#include <fstream>
#include <cctype> //isdigit

#include <SFML/Graphics/RenderTexture.hpp>

#include "BoardDataContainer.h"
#include "../Entity/Tile/GraphicTiles.h"
#include "../Entity/GraphicEntities.h"
#include "../Entity/Shape/Arrow/GraphicArrows.h"
#include "../Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "../Board/BoardLabels.h"
#include "../Entity/TurnToken/TurnToken.h"

using namespace sigrid;

Board::Board(){}

Board::Board(const Board& src){
    *this = src;
}

void Board::setPieceManagerPtr(PieceManager* const managerPtr){
    m_graphicBoard.setPieceManagerPtr(managerPtr);
}

void Board::setTileColorManagerPtr(ColorManager* const managerPtr){
    m_graphicBoard.setTileColorManagerPtr(managerPtr);
}

void Board::setArrowColorManagerPtr(ColorManager* const managerPtr){
    m_graphicBoard.setArrowColorManagerPtr(managerPtr);
}

void Board::setFontManagerPtr(FontManager* const managerPtr){
    m_graphicBoard.setFontManagerPtr(managerPtr);
}

void Board::setIconManagerPtr(IconManager* const managerPtr){
    m_graphicBoard.setIconManagerPtr(managerPtr);
}

void Board::setLeftToRight(){
    m_graphicBoard.setLeftToRight();
}

void Board::setRightToLeft(){
    m_graphicBoard.setRightToLeft();
}

void Board::setTopToBottom(){
    m_graphicBoard.setTopToBottom();
}

void Board::setBottomToTop(){
    m_graphicBoard.setBottomToTop();
}

void Board::loadBoardData(const BoardDataContainer& boardData){

    if(m_logicBoard.init(boardData)){
        m_graphicBoard.load(m_logicBoard);
    }
    else{
        std::cerr << "Board: Failed to load logicBoard" << std::endl;
    }
}

void Board::init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData){

    if(m_logicBoard.init(boardData)){
        m_graphicBoard.init(m_logicBoard, graphicData);
    }
    else{
        std::cerr << "Board: Failed to init logicBoard" << std::endl;
    }
}

Board& Board::operator=(const Board& rhs){
    m_filename = rhs.m_filename;
    m_imageFilename = rhs.m_imageFilename;
    m_logicBoard = rhs.m_logicBoard;
    m_graphicBoard = rhs.m_graphicBoard;
    
    if(rhs.m_selection){
        if(!m_selection){
            m_selection = std::make_unique<Coord>();
        }
        *m_selection = *(rhs.m_selection);
    }

    return *this;
}

void Board::setPosition(const sf::Vector2f& position){
    m_graphicBoard.setPosition(position);
}

void Board::setPositionX(const float x){
    m_graphicBoard.setPositionX(x);
}

void Board::setScale(const float scale){
    m_graphicBoard.setScale(scale);
}

void Board::setFilename(const std::string& filename){
    m_filename = filename;
}

void Board::setImageFilename(const std::string& filename){
    m_imageFilename = filename;
}

unsigned int Board::getNumColumns() const{
    return m_logicBoard.getNumColumns();
}

unsigned int Board::getImageWidth() const{
    return m_graphicBoard.getImageWidth();
}

unsigned int Board::getImageHeight() const{
    return m_graphicBoard.getImageHeight();
}

std::string Board::getHexStream() const{
    return m_graphicBoard.getHexStream();
}

float Board::getDisplayWidth() const{
    return m_graphicBoard.getDisplayWidth();
}

float Board::getDisplayHeight() const{
    return m_graphicBoard.getDisplayHeight();
}

std::string Board::getName() const{
    if(m_filename.size() == 0){
        return "";
    }
    auto end = m_filename.rfind('.');
    if(end == std::string::npos){
        end = m_filename.size()-1;
    }
    auto begin = m_filename.rfind('/');
    if(begin == std::string::npos){
        begin = 0;
    }
    else{
        begin++;
    }
    return m_filename.substr(begin, (end-begin));
}

std::string Board::getFilename() const{
    return m_filename;
}

std::string Board::getImageFilename() const{
    return m_imageFilename;
}

bool Board::contains(const sf::Vector2f& point) const{
    return m_graphicBoard.contains(point);
}

bool Board::isEmptyTile(const Coord& coord) const{
    return m_logicBoard.isEmptyTile(coord);
}

bool Board::isCoordinatesOutside() const{
    return m_graphicBoard.isCoordinatesOutside();
}

bool Board::isWithinTurnToken(const sf::Vector2f& point) const{
    return m_graphicBoard.isWithinTurnToken(point);
}

bool Board::isImageFilenameSet() const{
    return m_imageFilename.length() > 0;
}

std::optional<Coord> Board::getTileCoord(const sf::Vector2f& point){
    return m_graphicBoard.getTileCoord(point);
}

std::optional<LogicEntity> Board::getLogicEntity(const Coord& coord){
    auto entity_o = m_logicBoard.getEntityAt(coord);
    if(entity_o == std::nullopt){
        return std::nullopt;
    }
    return entity_o.value();
}


std::optional<LogicTile> Board::getTile(const Coord& coord){
    auto tile_o = m_logicBoard.getTile(coord);
    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    return tile_o.value();
}

std::optional<LogicArrow> Board::getLogicArrow(const CoordPair& coordPair){
    auto arrow_o = m_logicBoard.getArrowAt(coordPair);
    if(arrow_o == std::nullopt){
        return std::nullopt;
    }
    return arrow_o.value();
}

std::string Board::getFen() const{
    return m_logicBoard.getFen();
}

void Board::select(const Coord& newCoord){
    if(!m_selection){
        m_selection = std::make_unique<Coord>(newCoord);
        m_graphicBoard.highlightTile(newCoord);
        return;
    }

    Coord oldCoord = *m_selection;
    
    if(oldCoord == newCoord){
        m_selection = nullptr;
        m_graphicBoard.unhighlight();
        return;
    }

    if(m_logicBoard.isEmptyTile(oldCoord)){
        m_selection = std::make_unique<Coord>(newCoord);
        m_graphicBoard.highlightTile(newCoord);
        return;
    }

    if(m_logicBoard.moveEntity(oldCoord, newCoord)){
        m_graphicBoard.moveEntity(oldCoord, newCoord);
    }

    m_selection = nullptr;
    m_graphicBoard.unhighlight();
}

void Board::deselect(){
    m_selection = nullptr;
    m_graphicBoard.unhighlight();
}

void Board::addEntity(const Coord& coord, const LogicEntity& newEntity){

    if(!m_logicBoard.isWithinBoard(coord)){
        std::cerr << "Board: Failed to add Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_logicBoard.getEntityAt(coord);

    if(occupyingEntity_o != std::nullopt){
        std::cerr << "Board: Failed to add Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because the tile is already occupied" << std::endl;
        return;
    }

    if(m_logicBoard.addEntity(coord, newEntity)){
        m_graphicBoard.addEntity(coord, newEntity);
    }
}

void Board::removeEntity(const Coord& coord){

    if(!m_logicBoard.isWithinBoard(coord)){
        std::cerr << "Board: Failed to remove Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_logicBoard.getEntityAt(coord);

    if(occupyingEntity_o == std::nullopt){
        std::cerr << "Board: Failed to remove Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because there is no entity there" << std::endl;
        return;
    }

    if(m_logicBoard.removeEntity(coord)){
        m_graphicBoard.removeEntity(coord);
    }
}

void Board::addEntityAtSelection(const LogicEntity& newEntity){
    if(m_selection == nullptr){
        return;
    }
    addEntity(*m_selection, newEntity);
    m_selection = nullptr;
    m_graphicBoard.unhighlight();
}

void Board::addTileHighlight(const Coord& coord, const int& colorId){

    if(!m_logicBoard.isWithinBoard(coord)){
        std::cerr << "Board: Failed to add highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto tile_o = m_logicBoard.getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "Board: Failed to add highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "There is no tile there" << std::endl;
        return;
    }

    auto highlightColor_o = tile_o.value().getHighlightColorId();

    if(highlightColor_o != std::nullopt){
        std::cerr << "Board: Failed to add highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "There is already a highlight there" << std::endl;
        return;
    }

    if(m_logicBoard.addTileHighlight(coord, colorId)){
        m_graphicBoard.addTileHighlight(coord, colorId);
    }
}

void Board::removeTileHighlight(const Coord& coord){

    if(!m_logicBoard.isWithinBoard(coord)){
        std::cerr << "Board: Failed to remove highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto tile_o = m_logicBoard.getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "Board: Failed to remove highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "There is no tile there" << std::endl;
        return;
    }

    auto highlightColor_o = tile_o.value().getHighlightColorId();

    if(highlightColor_o == std::nullopt){
        std::cerr << "Board: Failed to remove highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "There is no highlight there" << std::endl;
        return;
    }

    if(m_logicBoard.removeTileHighlight(coord)){
        m_graphicBoard.removeTileHighlight(coord);
    }
}

void Board::dragAndDrop(const Coord& fromCoord, const Coord& toCoord){
    assert(fromCoord != toCoord);

    if(m_logicBoard.isEmptyTile(fromCoord)){
        return;
    }

    if(m_logicBoard.moveEntity(fromCoord, toCoord)){
        m_graphicBoard.moveEntity(fromCoord, toCoord);
    }
    
}

void Board::addArrow(const Coord& fromCoord, const Coord& toCoord, const LogicArrow& newArrow){

    if(!m_logicBoard.isWithinBoard(fromCoord)){
        std::cerr << "Board: Unable to add arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Starting tile is out of bounds" << std::endl;
        return;
    }

    if(!m_logicBoard.isWithinBoard(toCoord)){
        std::cerr << "Board: Unable to add arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Destination tile is out of bounds" << std::endl;
        return;
    }

    auto occupyingArrow_o = m_logicBoard.getArrowAt({fromCoord, toCoord});

    if(occupyingArrow_o != std::nullopt){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "There is already an arrow there" << std::endl;
        return;
    }

    if(m_logicBoard.addArrow({fromCoord, toCoord}, newArrow)){
        m_graphicBoard.addArrow({fromCoord, toCoord}, newArrow);
    }
}

void Board::removeArrow(const Coord& fromCoord, const Coord& toCoord){

    if(!m_logicBoard.isWithinBoard(fromCoord)){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Starting tile is out of bounds" << std::endl;
        return;
    }

    if(!m_logicBoard.isWithinBoard(toCoord)){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Destination tile is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_logicBoard.getArrowAt({fromCoord, toCoord});

    if(occupyingEntity_o == std::nullopt){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "There is no arrow there" << std::endl;
        return;
    }

    if(m_logicBoard.removeArrow({fromCoord, toCoord})){
        m_graphicBoard.removeArrow({fromCoord, toCoord});
    }
}

void Board::updateDragArrow(const Coord& fromCoord, const Coord& toCoord, const int& colorId){
    m_graphicBoard.updateDragArrow(fromCoord, toCoord, colorId);
}

void Board::removeDragArrow(){
    m_graphicBoard.removeDragArrow();
}

void Board::loadFen(const std::string& fen){

    std::cout << "Loading position from FEN: \"" << fen << "\"" << std::endl;

    clearEntities();
    int x = 0;
    int y = m_logicBoard.getNumRows()-1;
    int i;
    for(i = 0; i < fen.size(); i++){
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
    if(fen.length() >= i+1){
        char activeColorChar = fen.at(i+1);
        if(activeColorChar == 'b'){
            m_logicBoard.setTurnToMove(1);
            m_graphicBoard.setTurnToMove(1);
        }
        else{
            m_logicBoard.setTurnToMove(0);
            m_graphicBoard.setTurnToMove(0);
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
                std::cerr << "Failed to create folder: " << folder << std::endl;
                return false;
            }
        }

        endPos = filename.find('/',endPos+1);
    }
    return true;
}

void Board::save(){

    if(m_filename.length() == 0){
        std::cerr << "Unable to save board, filename is not set" << std::endl;
        return; 
    }

    std::cout << "Saving " << m_filename << std::endl;

    if(!createFolderForFile(m_filename)){
        std::cerr << "Saving failed" << std::endl;
        return;
    }

    std::ofstream out(m_filename);

    if(!out.is_open()){
        std::cerr << "Failed to open " << m_filename << std::endl;
        std::cerr << "Saving failed" << std::endl;
        return;
    }

    out << m_logicBoard;    

    std::cout << "Saved " << m_filename << std::endl;

    if(m_imageFilename.length() == 0){
        std::cerr << "Unable to save board image, filename is not set" << std::endl;
        return;
    }

    out << "\nImageFilename: " << m_imageFilename;

    if(!(createFolderForFile(m_imageFilename))){
        std::cerr << "Saving board image failed" << std::endl;
        return;
    }

    m_graphicBoard.saveImage(m_imageFilename);
}

void Board::clearEntities(){
    m_logicBoard.clearEntities();
    m_graphicBoard.clearEntities();
}

void Board::clearArrows(){
    m_logicBoard.clearArrows();
    m_graphicBoard.clearArrows();
}

void Board::print(){
    m_logicBoard.print();
}

void Board::flipBoard(){
    m_graphicBoard.flip();
}

void Board::addLeftInsideLabels(){
    m_graphicBoard.addLeftInsideLabels();
}

void Board::addBottomInsideLabels(){
    m_graphicBoard.addBottomInsideLabels();
}

void Board::addLeftOutsideLabels(){
    m_graphicBoard.addLeftOutsideLabels();
}

void Board::addRightOutsideLabels(){
    m_graphicBoard.addRightOutsideLabels();
}

void Board::addTopOutsideLabels(){
    m_graphicBoard.addTopOutsideLabels();
}

void Board::addBottomOutsideLabels(){
    m_graphicBoard.addBottomOutsideLabels();
}

void Board::removeLeftInsideLabels(){
    m_graphicBoard.removeLeftInsideLabels();
}

void Board::removeBottomInsideLabels(){
    m_graphicBoard.removeBottomInsideLabels();
}

void Board::removeLeftOutsideLabels(){
    m_graphicBoard.removeLeftOutsideLabels();
}

void Board::removeRightOutsideLabels(){
    m_graphicBoard.removeRightOutsideLabels();
}

void Board::removeTopOutsideLabels(){
    m_graphicBoard.removeTopOutsideLabels();
}

void Board::removeBottomOutsideLabels(){
    m_graphicBoard.removeBottomOutsideLabels();
}

void Board::setCoordinateSize(const float& size){
    m_graphicBoard.setCoordinateSize(size);
}

void Board::addTileColumnRight(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_logicBoard.addTileColumnRight()){
            m_graphicBoard.addTileColumnRight(m_logicBoard.getRepeatColorIds());
        }
    }
    else{
        if(m_logicBoard.addTileColumnLeft()){
            m_graphicBoard.addTileColumnLeft(m_logicBoard.getRepeatColorIds());
        }
    }
    
    deselect();
}

void Board::addTileColumnLeft(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_logicBoard.addTileColumnLeft()){
            m_graphicBoard.addTileColumnLeft(m_logicBoard.getRepeatColorIds());
        }
    }
    else{
        if(m_logicBoard.addTileColumnRight()){
            m_graphicBoard.addTileColumnRight(m_logicBoard.getRepeatColorIds());
        }
    }
    
    deselect();
}

void Board::removeTileColumnRight(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_logicBoard.removeTileColumnRight()){
            m_graphicBoard.removeTileColumnRight();
        }
    }
    else{
        if(m_logicBoard.removeTileColumnLeft()){
            m_graphicBoard.removeTileColumnLeft();
        }
    }

    deselect();
}

void Board::removeTileColumnLeft(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_logicBoard.removeTileColumnLeft()){
            m_graphicBoard.removeTileColumnLeft();
        }
    }
    else{
        if(m_logicBoard.removeTileColumnRight()){
            m_graphicBoard.removeTileColumnRight();
        }
    }
    
    deselect();
}

void Board::addTileRowUp(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_logicBoard.addTileRowUp()){
            m_graphicBoard.addTileRowUp(m_logicBoard.getRepeatColorIds());
        }
    }
    else{
        if(m_logicBoard.addTileRowDown()){
            m_graphicBoard.addTileRowDown(m_logicBoard.getRepeatColorIds());
        }
    }
    
    deselect();
}

void Board::addTileRowDown(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_logicBoard.addTileRowDown()){
            m_graphicBoard.addTileRowDown(m_logicBoard.getRepeatColorIds());
        }
    }
    else{
        if(m_logicBoard.addTileRowUp()){
            m_graphicBoard.addTileRowUp(m_logicBoard.getRepeatColorIds());
        }
    }
    
    deselect();
}

void Board::removeTileRowUp(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_logicBoard.removeTileRowUp()){
            m_graphicBoard.removeTileRowUp();
        }
    }
    else{
        if(m_logicBoard.removeTileRowDown()){
            m_graphicBoard.removeTileRowDown();
        }
    }

    deselect();
}

void Board::removeTileRowDown(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_logicBoard.removeTileRowDown()){
            m_graphicBoard.removeTileRowDown();
        }
    }
    else{
        if(m_logicBoard.removeTileRowUp()){
            m_graphicBoard.removeTileRowUp();
        }
    }
    
    deselect();
}

void Board::addBorder(){
    m_graphicBoard.addBorder();
}

void Board::removeBorder(){
    m_graphicBoard.removeBorder();
}

void Board::addTurnToken(){
    m_graphicBoard.addTurnToken(m_logicBoard.getTurnToMove());
}

void Board::removeTurnToken(){
    m_graphicBoard.removeTurnToken();
}

void Board::toggleTurnToken(){
    int turnToMove = m_logicBoard.getTurnToMove();
    if(turnToMove == 0){
        m_logicBoard.setTurnToMove(1);
        m_graphicBoard.setTurnToMove(1);
    }
    else if(turnToMove == 1){
        m_logicBoard.setTurnToMove(0);
        m_graphicBoard.setTurnToMove(0);
    }
}

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_graphicBoard);
}