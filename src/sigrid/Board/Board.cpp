#include "sigrid/Board/Board.h"

#include <iostream>
#include <fstream>
#include <cctype> //isdigit

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Image.hpp>

#include "sigrid/utilities/FileSystem/FileSystem.h"
#include "sigrid/Board/BoardDesignContainer.h"
#include "sigrid/Board/BoardStateContainer.h"
#include "sigrid/Entity/Tile/GraphicTiles.h"
#include "sigrid/Entity/GraphicEntities.h"
#include "sigrid/Entity/Shape/Arrow/GraphicArrows.h"
#include "sigrid/Entity/Shape/RectangleBorder/RectangleBorder.h"
#include "sigrid/Board/BoardLabels.h"
#include "sigrid/Entity/TurnToken/TurnToken.h"

void sigrid::Board::setPieceManagerPtr(PieceManager* const managerPtr){
    m_graphicBoard.setPieceManagerPtr(managerPtr);
}

void sigrid::Board::setTileColorManagerPtr(ColorManager* const managerPtr){
    m_graphicBoard.setTileColorManagerPtr(managerPtr);
}

void sigrid::Board::setArrowColorManagerPtr(ColorManager* const managerPtr){
    m_graphicBoard.setArrowColorManagerPtr(managerPtr);
}

void sigrid::Board::setFontManagerPtr(FontManager* const managerPtr){
    m_graphicBoard.setFontManagerPtr(managerPtr);
}

void sigrid::Board::setIconManagerPtr(IconManager* const managerPtr){
    m_graphicBoard.setIconManagerPtr(managerPtr);
}

void sigrid::Board::setLeftToRight(){
    m_graphicBoard.setLeftToRight();
}

void sigrid::Board::setRightToLeft(){
    m_graphicBoard.setRightToLeft();
}

void sigrid::Board::setTopToBottom(){
    m_graphicBoard.setTopToBottom();
}

void sigrid::Board::setBottomToTop(){
    m_graphicBoard.setBottomToTop();
}

sigrid::BoardContainer sigrid::Board::getContainer() const{

    sigrid::BoardContainer container;
    container.stateFilename = m_filename;
    container.imageFilename = m_imageFilename;

    return container;
}

void sigrid::Board::loadGraphicData(const sigrid::BoardDesignContainer& graphicData){
    m_graphicBoard.loadDesign(graphicData);
}

sigrid::BoardDesignContainer sigrid::Board::getStyleContainer() const{
    return m_graphicBoard.getStyleContainer();
}

void sigrid::Board::loadBoardState(const sigrid::BoardStateContainer& boardStateData){

    if(m_state.load(boardStateData)){
        m_graphicBoard.loadBoardState(m_state);
    }
    else{
        std::cerr << "Board: Failed to load boardState" << std::endl;
    }
}

void sigrid::Board::setPosition(const sigrid::Position_f& position){
    m_graphicBoard.setPosition(position);
}

void sigrid::Board::setPositionX(const float x){
    m_graphicBoard.setPositionX(x);
}

void sigrid::Board::setScale(const float scale){
    m_graphicBoard.setScale(scale);
}

void sigrid::Board::setFilename(const sigrid::String& filename){
    m_filename = filename;
}

void sigrid::Board::setImageFilename(const sigrid::String& filename){
    m_imageFilename = filename;
}

int sigrid::Board::getNumColumns() const{
    return m_state.getNumColumns();
}

int sigrid::Board::getImageWidth() const{
    return m_graphicBoard.getImageWidth();
}

int sigrid::Board::getImageHeight() const{
    return m_graphicBoard.getImageHeight();
}

sigrid::Image sigrid::Board::getImage(const int maxWidth, const int maxHeight) const{
    return m_graphicBoard.getImage(maxWidth, maxHeight);
}

const sigrid::Position_f& sigrid::Board::getTopLeftPosition() const{
    return m_graphicBoard.getTopLeftPosition();
}

sigrid::Size_f sigrid::Board::getDisplaySize() const{
    return m_graphicBoard.getDisplaySize();
}

float sigrid::Board::getDisplayWidth() const{
    return m_graphicBoard.getDisplayWidth();
}

float sigrid::Board::getDisplayHeight() const{
    return m_graphicBoard.getDisplayHeight();
}

sigrid::String sigrid::Board::getName() const{

    if(m_filename.length() == 0){
        return "";
    }
    int end;
    auto end_o = m_filename.rfind('.');
    if(end_o == std::nullopt){
        end = m_filename.length()-1;
    }
    else{
        end = end_o.value();
    }

    int begin;
    auto begin_o = m_filename.rfind('/');
    if(begin_o == std::nullopt){
        begin = 0;
    }
    else{
        begin = begin_o.value() + 1;
    }

    auto name_o = m_filename.substr(begin, (end-begin));
    if(name_o == std::nullopt){
        return "";
    }
    return name_o.value();
}

sigrid::String sigrid::Board::getFilename() const{
    return m_filename;
}

sigrid::String sigrid::Board::getImageFilename() const{
    return m_imageFilename;
}

bool sigrid::Board::contains(const sigrid::Position_f& point) const{
    return m_graphicBoard.contains(point);
}

sigrid_list::Vector<int> sigrid::Board::getRepeatTileColorIds() const{
    return m_state.getRepeatColorIds();
}

bool sigrid::Board::isEmptyTile(const sigrid_coord::Coord& coord) const{
    return m_state.isEmptyTile(coord);
}

bool sigrid::Board::isCoordinatesOutside() const{
    return m_graphicBoard.isCoordinatesOutside();
}

bool sigrid::Board::isWithinTurnToken(const sigrid::Position_f& point) const{
    return m_graphicBoard.isWithinTurnToken(point);
}

bool sigrid::Board::isImageFilenameSet() const{
    return m_imageFilename.length() > 0;
}

std::optional<sigrid_coord::Coord> sigrid::Board::getTileCoord(const sigrid::Position_f& point){
    return m_graphicBoard.getTileCoord(point);
}

std::optional<sigrid::LogicEntity> sigrid::Board::getLogicEntity(const sigrid_coord::Coord& coord){
    auto entity_o = m_state.getEntityAt(coord);
    if(entity_o == std::nullopt){
        return std::nullopt;
    }
    return entity_o.value();
}


std::optional<sigrid::LogicTile> sigrid::Board::getTile(const sigrid_coord::Coord& coord){
    auto tile_o = m_state.getTile(coord);
    if(tile_o == std::nullopt){
        return std::nullopt;
    }
    return tile_o.value();
}

std::optional<sigrid::LogicArrow> sigrid::Board::getLogicArrow(const sigrid_coord::CoordPair& coordPair){
    auto arrow_o = m_state.getArrowAt(coordPair);
    if(arrow_o == std::nullopt){
        return std::nullopt;
    }
    return arrow_o.value();
}

sigrid::String sigrid::Board::getFen() const{
    return m_state.getFen();
}

void sigrid::Board::select(const sigrid_coord::Coord& newCoord){
    
    if(m_selection_o == std::nullopt){
        m_selection_o = newCoord;
        m_graphicBoard.highlightTile(newCoord);
        return;
    }
    sigrid_coord::Coord oldCoord = m_selection_o.value();
    
    if(oldCoord == newCoord){
        m_selection_o = std::nullopt;
        m_graphicBoard.unhighlight();
        return;
    }

    if(m_state.isEmptyTile(oldCoord)){
        m_selection_o = newCoord;
        m_graphicBoard.highlightTile(newCoord);
        return;
    }

    if(m_state.moveEntity(oldCoord, newCoord)){
        m_graphicBoard.moveEntity(oldCoord, newCoord);
    }

    m_selection_o = std::nullopt;
    m_graphicBoard.unhighlight();
}

void sigrid::Board::deselect(){
    m_selection_o = std::nullopt;
    m_graphicBoard.unhighlight();
}

void sigrid::Board::addEntity(const sigrid_coord::Coord& coord, const LogicEntity& newEntity){

    if(!m_state.isWithinBoard(coord)){
        std::cerr << "Board: Failed to add Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_state.getEntityAt(coord);

    if(occupyingEntity_o != std::nullopt){
        std::cerr << "Board: Failed to add Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because the tile is already occupied" << std::endl;
        return;
    }

    if(m_state.addEntity(coord, newEntity)){
        m_graphicBoard.addEntity(coord, newEntity);
    }
}

void sigrid::Board::removeEntity(const sigrid_coord::Coord& coord){

    if(!m_state.isWithinBoard(coord)){
        std::cerr << "Board: Failed to remove Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_state.getEntityAt(coord);

    if(occupyingEntity_o == std::nullopt){
        std::cerr << "Board: Failed to remove Entity at " << coord.getNotation() << std::endl;
        std::cerr << "because there is no entity there" << std::endl;
        return;
    }

    if(m_state.removeEntity(coord)){
        m_graphicBoard.removeEntity(coord);
    }
}

void sigrid::Board::addEntityAtSelection(const LogicEntity& newEntity){
    
    if(m_selection_o == std::nullopt){
        return;
    }
    auto& selection = m_selection_o.value();

    addEntity(selection, newEntity);
    m_selection_o = std::nullopt;
    m_graphicBoard.unhighlight();
}

void sigrid::Board::addTileHighlight(const sigrid_coord::Coord& coord, const int& colorId){

    if(!m_state.isWithinBoard(coord)){
        std::cerr << "Board: Failed to add highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto tile_o = m_state.getTile(coord);

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

    if(m_state.addTileHighlight(coord, colorId)){
        m_graphicBoard.addTileHighlight(coord, colorId);
    }
}

void sigrid::Board::removeTileHighlight(const sigrid_coord::Coord& coord){

    if(!m_state.isWithinBoard(coord)){
        std::cerr << "Board: Failed to remove highlight at "
            << coord.getNotation() << std::endl;
        std::cerr << "because it is out of bounds" << std::endl;
        return;
    }

    auto tile_o = m_state.getTile(coord);

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

    if(m_state.removeTileHighlight(coord)){
        m_graphicBoard.removeTileHighlight(coord);
    }
}

void sigrid::Board::dragAndDrop(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord){
    
    assert(fromCoord != toCoord);

    if(m_state.isEmptyTile(fromCoord)){
        return;
    }

    if(m_state.moveEntity(fromCoord, toCoord)){
        m_graphicBoard.moveEntity(fromCoord, toCoord);
    }
    
}

void sigrid::Board::addArrow(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const LogicArrow& newArrow){

    if(!m_state.isWithinBoard(fromCoord)){
        std::cerr << "Board: Unable to add arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Starting tile is out of bounds" << std::endl;
        return;
    }

    if(!m_state.isWithinBoard(toCoord)){
        std::cerr << "Board: Unable to add arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Destination tile is out of bounds" << std::endl;
        return;
    }

    auto occupyingArrow_o = m_state.getArrowAt({fromCoord, toCoord});

    if(occupyingArrow_o != std::nullopt){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "There is already an arrow there" << std::endl;
        return;
    }

    if(m_state.addArrow({fromCoord, toCoord}, newArrow)){
        m_graphicBoard.addArrow({fromCoord, toCoord}, newArrow);
    }
}

void sigrid::Board::removeArrow(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord){

    if(!m_state.isWithinBoard(fromCoord)){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Starting tile is out of bounds" << std::endl;
        return;
    }

    if(!m_state.isWithinBoard(toCoord)){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "Destination tile is out of bounds" << std::endl;
        return;
    }

    auto occupyingEntity_o = m_state.getArrowAt({fromCoord, toCoord});

    if(occupyingEntity_o == std::nullopt){
        std::cerr << "Board: Unable to remove arrow "
            << fromCoord.getNotation() << "-"
            << toCoord.getNotation() << std::endl;
        std::cerr << "There is no arrow there" << std::endl;
        return;
    }

    if(m_state.removeArrow({fromCoord, toCoord})){
        m_graphicBoard.removeArrow({fromCoord, toCoord});
    }
}

void sigrid::Board::updateDragArrow(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const int& colorId){
    m_graphicBoard.updateDragArrow(fromCoord, toCoord, colorId);
}

void sigrid::Board::removeDragArrow(){
    m_graphicBoard.removeDragArrow();
}

void sigrid::Board::loadFen(const sigrid::String& fen){

    std::cout << "Loading position from FEN: \"" << fen << "\"" << std::endl;

    clearEntities();
    int x = 0;
    int y = m_state.getNumRows()-1;
    int i;
    for(i = 0; i < fen.length(); i++){
        auto string_o = fen.substr(i, 1);
        if(string_o == std::nullopt){
            return;
        }
        sigrid::String s = string_o.value();

        if(s == " "){
            break;
        }
        else if(s.isDigits()){
            auto digit_o = s.toInt();
            if(digit_o == std::nullopt){
                return;
            }
            int digit = digit_o.value();
            x+= digit;
        }
        else if(s == "/"){
            x = 0;
            y--;
        }
        else{
            int colorId;
            if(s.isUpper()){
                colorId = 0;
            }
            else{
                colorId = 1;
            }
            s.toUpper();
            LogicPiece logicPiece;
            logicPiece.setNotation(s);
            logicPiece.setColorId(colorId);

            addEntity({x,y}, logicPiece);
            x++;
        }
    }
    if(fen.length() >= i+1){
        auto activeColorChar_o = fen.at(i+i);
        if(activeColorChar_o == std::nullopt){
            return;
        }
        char activeColorChar = activeColorChar_o.value().get();
        
        if(activeColorChar == 'b'){
            m_state.setTurnToMove(1);
            m_graphicBoard.setTurnToMove(1);
        }
        else{
            m_state.setTurnToMove(0);
            m_graphicBoard.setTurnToMove(0);
        }
    }
}

void sigrid::Board::save(){

    if(m_filename.length() == 0){
        std::cerr << "Board: Unable to save board, filename is not set" << std::endl;
        return; 
    }

    std::cout << "Saving " << m_filename << std::endl;

    if(!sigrid_filesystem::createFolderForFile(m_filename)){
        std::cerr << "Board: Saving failed" << std::endl;
        return;
    }

    std::ofstream out(m_filename.getStdString());

    if(!out.is_open()){
        std::cerr << "Board: Failed to open " << m_filename << std::endl;
        std::cerr << "Saving failed" << std::endl;
        return;
    }

    BoardStateContainer boardStateContainer = m_state.getContainer();

    out << boardStateContainer.getString(0).getStdString();

    std::cout << "Saved " << m_filename << std::endl;

    if(m_imageFilename.length() == 0){
        std::cerr << "Board: Unable to save board image, filename is not set" << std::endl;
        return;
    }

    if(!(sigrid_filesystem::createFolderForFile(m_imageFilename))){
        std::cerr << "Board: Saving board image failed" << std::endl;
        return;
    }

    m_graphicBoard.saveImage(m_imageFilename);
}

void sigrid::Board::clearEntities(){
    m_state.clearEntities();
    m_graphicBoard.clearEntities();
}

void sigrid::Board::clearArrows(){
    m_state.clearArrows();
    m_graphicBoard.clearArrows();
}

void sigrid::Board::print(){
    m_state.print();
}

void sigrid::Board::flipBoard(){
    m_graphicBoard.flip();
}

void sigrid::Board::addLeftInsideLabels(){
    m_graphicBoard.addLeftInsideLabels();
}

void sigrid::Board::addBottomInsideLabels(){
    m_graphicBoard.addBottomInsideLabels();
}

void sigrid::Board::addLeftOutsideLabels(){
    m_graphicBoard.addLeftOutsideLabels();
}

void sigrid::Board::addRightOutsideLabels(){
    m_graphicBoard.addRightOutsideLabels();
}

void sigrid::Board::addTopOutsideLabels(){
    m_graphicBoard.addTopOutsideLabels();
}

void sigrid::Board::addBottomOutsideLabels(){
    m_graphicBoard.addBottomOutsideLabels();
}

void sigrid::Board::removeLeftInsideLabels(){
    m_graphicBoard.removeLeftInsideLabels();
}

void sigrid::Board::removeBottomInsideLabels(){
    m_graphicBoard.removeBottomInsideLabels();
}

void sigrid::Board::removeLeftOutsideLabels(){
    m_graphicBoard.removeLeftOutsideLabels();
}

void sigrid::Board::removeRightOutsideLabels(){
    m_graphicBoard.removeRightOutsideLabels();
}

void sigrid::Board::removeTopOutsideLabels(){
    m_graphicBoard.removeTopOutsideLabels();
}

void sigrid::Board::removeBottomOutsideLabels(){
    m_graphicBoard.removeBottomOutsideLabels();
}

void sigrid::Board::setCoordinateSize(const float& size){
    m_graphicBoard.setCoordinateSize(size);
}

void sigrid::Board::addTileColumnRight(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_state.addTileColumnRight()){
            m_graphicBoard.addTileColumnRight(m_state.getRepeatColorIds());
        }
    }
    else{
        if(m_state.addTileColumnLeft()){
            m_graphicBoard.addTileColumnLeft(m_state.getRepeatColorIds());
        }
    }
    
    deselect();
}

void sigrid::Board::addTileColumnLeft(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_state.addTileColumnLeft()){
            m_graphicBoard.addTileColumnLeft(m_state.getRepeatColorIds());
        }
    }
    else{
        if(m_state.addTileColumnRight()){
            m_graphicBoard.addTileColumnRight(m_state.getRepeatColorIds());
        }
    }
    
    deselect();
}

void sigrid::Board::removeRightTileColumn(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_state.removeRightTileColumn()){
            m_graphicBoard.removeRightTileColumn();
        }
    }
    else{
        if(m_state.removeLeftTileColumn()){
            m_graphicBoard.removeLeftTileColumn();
        }
    }

    deselect();
}

void sigrid::Board::removeLeftTileColumn(){

    if(m_graphicBoard.isLeftToRight()){
        if(m_state.removeLeftTileColumn()){
            m_graphicBoard.removeLeftTileColumn();
        }
    }
    else{
        if(m_state.removeRightTileColumn()){
            m_graphicBoard.removeRightTileColumn();
        }
    }
    
    deselect();
}

void sigrid::Board::addTileRowUp(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_state.addTileRowUp()){
            m_graphicBoard.addTileRowUp(m_state.getRepeatColorIds());
        }
    }
    else{
        if(m_state.addTileRowDown()){
            m_graphicBoard.addTileRowDown(m_state.getRepeatColorIds());
        }
    }
    
    deselect();
}

void sigrid::Board::addTileRowDown(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_state.addTileRowDown()){
            m_graphicBoard.addTileRowDown(m_state.getRepeatColorIds());
        }
    }
    else{
        if(m_state.addTileRowUp()){
            m_graphicBoard.addTileRowUp(m_state.getRepeatColorIds());
        }
    }
    
    deselect();
}

void sigrid::Board::removeTopTileRow(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_state.removeTopTileRow()){
            m_graphicBoard.removeTopTileRow();
        }
    }
    else{
        if(m_state.removeBottomTileRow()){
            m_graphicBoard.removeBottomTileRow();
        }
    }

    deselect();
}

void sigrid::Board::removeBottomTileRow(){

    if(m_graphicBoard.isTopToBottom()){
        if(m_state.removeBottomTileRow()){
            m_graphicBoard.removeBottomTileRow();
        }
    }
    else{
        if(m_state.removeTopTileRow()){
            m_graphicBoard.removeTopTileRow();
        }
    }
    
    deselect();
}

void sigrid::Board::addBorder(){
    m_graphicBoard.addBorder();
}

void sigrid::Board::removeBorder(){
    m_graphicBoard.removeBorder();
}

void sigrid::Board::addTurnToken(){
    m_graphicBoard.addTurnToken(m_state.getTurnToMove());
}

void sigrid::Board::removeTurnToken(){
    m_graphicBoard.removeTurnToken();
}

void sigrid::Board::toggleTurnToken(){
    int turnToMove = m_state.getTurnToMove();
    if(turnToMove == 0){
        m_state.setTurnToMove(1);
        m_graphicBoard.setTurnToMove(1);
    }
    else if(turnToMove == 1){
        m_state.setTurnToMove(0);
        m_graphicBoard.setTurnToMove(0);
    }
}

void sigrid::Board::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(m_graphicBoard);
}