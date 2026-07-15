#include "Board/LogicBoard.h"

#include "Board/BoardDataContainer.h"

#include <iostream>

using namespace sigrid;

bool LogicBoard::init(const BoardDataContainer& data){

    m_tileLayer.clear();
    m_pieceLayer.clear();
    m_arrowLayer.clear();
    m_turnToMove = 0;

    if(data.repeatTileColorIds.size() == 0){
        std::cerr << "LogicBoard: Failed to setup LogicBoard: Default tile colors not set" << std::endl;
        return false;
    }

    m_tileLayer.init(data.columns, data.rows, data.repeatTileColorIds);

    for(const auto pieceContainer : data.logicPieces){

        sigrid_coord::Coord coord{pieceContainer.position};

        if(coord.y < 0){
            std::cerr << "LogicBoard: Failed to set piece at " << coord.getNotation() << ", missing row on board" << std::endl;
            continue;
        }
        if(coord.y >= getNumRows()){
            std::cerr << "LogicBoard: Failed to set piece at " << coord.getNotation() << ", missing row on board" << std::endl;
            continue;
        }
        if(coord.x < 0){
            std::cerr << "LogicBoard: Failed to set piece at " << coord.getNotation() << ", missing column on board" << std::endl;
            continue;
        }
        if(coord.x >= getNumColumns()){
            std::cerr << "LogicBoard: Failed to set piece at " << coord.getNotation() << ", missing column on board" << std::endl;
            continue;
        }
        m_pieceLayer.addEntity(coord, LogicPiece(pieceContainer.name, pieceContainer.colorId));
    }

    for(const auto cData : data.logicCircles){

        sigrid_coord::Coord coord{cData.position};

        if(!isWithinBoard(coord)){
            std::cerr << "LogicBoard constructor: Failed to set circle at " << coord.getNotation() << std::endl;
            std::cerr << "coordinate is outside of board" << std::endl;
            continue;
        }

        m_pieceLayer.addEntity(coord, LogicCircle{cData.colorId});
    }

    return true;
}

const int LogicBoard::getNumColumns() const{
    return m_tileLayer.getNumColumns();
}

const int LogicBoard::getNumRows() const{
    return m_tileLayer.getNumRows();
}

bool LogicBoard::isWithinBoard(const sigrid_coord::Coord& coord) const{
    if(coord.x >= getNumColumns()){
        return false;
    }
    if(coord.y >= getNumRows()){
        return false;
    }
    return true;
}

bool LogicBoard::isEmptyTile(const sigrid_coord::Coord& coord) const{
    if(!isWithinBoard(coord)){
        return false;
    }
    return m_pieceLayer.getEntityAt(coord) == std::nullopt;
}

std::optional<LogicTile> LogicBoard::getTile(const sigrid_coord::Coord& coord) const{

    auto tile_o = m_tileLayer.getTile(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }

    return tile_o.value();
}

std::optional<LogicEntity> LogicBoard::getEntityAt(const sigrid_coord::Coord& coord) const{
    return m_pieceLayer.getEntityAt(coord);
}

std::optional<LogicArrow> LogicBoard::getArrowAt(const sigrid_coord::CoordPair& coordPair) const{

    auto arrow_o = m_arrowLayer.getArrow(coordPair);

    if(arrow_o == std::nullopt){
        return std::nullopt;
    }

    return arrow_o.value();
}

std::string LogicBoard::getFen() const{

    std::string fen;

    for(int y = getNumRows()-1; y >= 0; y--){
        int i = 0;
        for(int x = 0; x < getNumColumns();x++){
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
    fen.append(" ");
    if(m_turnToMove == 0){
        fen.append("w");
    }
    else{
        fen.append("b");
    }
    fen.append(" KQkq - 0 1");

    return fen;
}

int LogicBoard::getTurnToMove() const{
    return m_turnToMove;
}

std::vector<int> LogicBoard::getRepeatColorIds() const{
    return m_tileLayer.getRepeatColorIds();
}

void LogicBoard::setTurnToMove(const int& turnToMove){
    m_turnToMove = turnToMove;
}

bool LogicBoard::addEntity(const sigrid_coord::Coord& coord, const LogicEntity& entity){

    if(!isWithinBoard(coord)){
        std::cerr << "LogicBoard: Unable to add entity at " << coord.getNotation() << std::endl;
        std::cerr << "The tile is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.getEntityAt(coord) != std::nullopt){
        std::cerr << "LogicBoard: Unable to add entity at " << coord.getNotation() << std::endl;
        std::cerr << "The tile is already occupied" << std::endl;
        return false;
    }

    m_pieceLayer.addEntity(coord,entity);
    return true;
}

bool LogicBoard::removeEntity(const sigrid_coord::Coord& coord){

    if(!isWithinBoard(coord)){
        std::cerr << "LogicBoard: Unable to remove entity at " << coord.getNotation() << std::endl;
        std::cerr << "The tile is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.getEntityAt(coord) == std::nullopt){
        std::cerr << "LogicBoard: Unable to remove entity at " << coord.getNotation() << std::endl;
        std::cerr << "There is no entity there" << std::endl;
        return false;
    }

    m_pieceLayer.removeEntity(coord);
    return true;
}

bool LogicBoard::moveEntity(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord){

    if(fromCoord.x == toCoord.x && fromCoord.y == toCoord.y){
        std::cerr << "LogicBoard: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cerr << "both coordinates are the same" << std::endl;
        return false;
    }

    if(!isWithinBoard(fromCoord)){
        std::cerr << "LogicBoard: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cerr << "starting tile is out of bounds" << std::endl;
        return false;
    }

    if(!isWithinBoard(toCoord)){
        std::cerr << "LogicBoard: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cerr << "destination tile is out of bounds" << std::endl;
        return false;
    }

    if(isEmptyTile(fromCoord)){
        std::cerr << "LogicBoard: Unable to move entity from " << fromCoord.getNotation() << std::endl;
        std::cerr << "No piece is standing there" << std::endl;
        return false;
    }

    if(!isEmptyTile(toCoord)){
        m_pieceLayer.removeEntity(toCoord);
    }

    m_pieceLayer.moveEntity(fromCoord, toCoord);
    return true;
}

bool LogicBoard::addTileHighlight(const sigrid_coord::Coord& coord, const int& highlightColorId){

    if(highlightColorId < 0){
        std::cerr << "LogicBoard: Unable to add highlight." << std::endl;
        std::cerr << "ColorId is not set (value: " << highlightColorId << ")" << std::endl;
        return false;
    }

    auto tile_o = m_tileLayer.getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "LogicBoard: Unable to add highlight." << std::endl;
        std::cerr << "Coord is not a valid tile (value:" << coord.getNotation() << ")" << std::endl;
        return false;
    }

    m_tileLayer.setHighlightColor(coord, highlightColorId);
    return true;
}

bool LogicBoard::removeTileHighlight(const sigrid_coord::Coord& coord){

    auto tile_o = m_tileLayer.getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "LogicBoard: Unable to add highlight." << std::endl;
        std::cerr << "Coord is not a valid tile (value:" << coord.getNotation() << ")" << std::endl;
        return false;
    }

    m_tileLayer.removeHighlight(coord);
    return true;
}

bool LogicBoard::addArrow(const sigrid_coord::CoordPair& coordPair, const LogicArrow& arrow){

    if(!isWithinBoard(coordPair.from)){
        std::cerr << "LogicBoard: Unable to add arrow from tile: " << coordPair.from.getNotation() << std::endl;
        std::cerr << "Starting tile is outside of the board" << std::endl;
        return false;
    }

    if(!isWithinBoard(coordPair.to)){
        std::cerr << "LogicBoard: Unable to add arrow to tile: " << coordPair.to.getNotation() << std::endl;
        std::cerr << "Destination tile is outside of the board" << std::endl;
        return false;
    }

    if(arrow.getColorId() < 0){
        std::cerr << "LogicBoard: Unable to add arrow" << std::endl;
        std::cerr << "ColorId is not set (value: " << arrow.getColorId() << ")" << std::endl;
        return false;
    }

    auto occupyingArrow_o = m_arrowLayer.getArrow(coordPair);

    if(occupyingArrow_o != std::nullopt){
        std::cerr << "LogicBoard: Unable to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "There is already an arrow there" << std::endl;
        return false;
    }

    m_arrowLayer.addArrow(coordPair, arrow);
    return true;
}


bool LogicBoard::removeArrow(const sigrid_coord::CoordPair& coordPair){

    auto occupyingArrow_o = m_arrowLayer.getArrow(coordPair);

    if(occupyingArrow_o == std::nullopt){
        std::cerr << "LogicBoard: Unable to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "There is no arrow there" << std::endl;
        return false;
    }

    m_arrowLayer.removeArrow(coordPair);
    return true;
}

bool LogicBoard::addTileColumnRight(){
    return m_tileLayer.addColumnRight();
}

bool LogicBoard::addTileColumnLeft(){
    if(!m_tileLayer.addColumnLeft()){
        return false;
    }
    m_pieceLayer.moveEntitiesRight();
    m_arrowLayer.moveArrowsRight();
    return true;
}

bool LogicBoard::removeRightTileColumn(){
    if(!m_tileLayer.removeRightColumn()){
        return false;
    }
    int columnId = m_tileLayer.getNumColumns();
    m_pieceLayer.removeColumn(columnId);
    m_arrowLayer.removeColumn(columnId);
    return true;
}

bool LogicBoard::removeLeftTileColumn(){
    if(!m_tileLayer.removeLeftColumn()){
        return false;
    }
    m_pieceLayer.removeColumn(0);
    m_pieceLayer.moveEntitiesLeft();
    m_arrowLayer.removeColumn(0);
    m_arrowLayer.moveArrowsLeft();
    return true;
}

bool LogicBoard::addTileRowUp(){
    if(!m_tileLayer.addRowUp()){
        return false;
    }
    m_pieceLayer.moveEntitiesDown();
    m_arrowLayer.moveArrowsDown();
    return true;
}

bool LogicBoard::addTileRowDown(){
    return m_tileLayer.addRowDown();
}

bool LogicBoard::removeTopTileRow(){
    if(!m_tileLayer.removeTopRow()){
        return false;
    }
    m_pieceLayer.removeRow(0);
    m_pieceLayer.moveEntitiesUp();
    m_arrowLayer.removeRow(0);
    m_arrowLayer.moveArrowsUp();
    return true;
}

bool LogicBoard::removeBottomTileRow(){
    if(!m_tileLayer.removeBottomRow()){
        return false;
    }
    int rowId = m_tileLayer.getNumRows();
    m_pieceLayer.removeRow(rowId);
    m_arrowLayer.removeRow(rowId);
    return true;
}

void LogicBoard::print(){
    std::cout << "Printing board" << std::endl;
    std::cout << "Number of columns: " << getNumColumns() << std::endl;
    std::cout << "Number of rows: " << getNumRows() << std::endl;
    
    for(int y = 0; y < getNumRows(); y++){
        for(int x = 0; x < getNumColumns(); x++){
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

void LogicBoard::clearEntities(){
    m_pieceLayer.clear();
}

void LogicBoard::clearArrows(){
    m_arrowLayer.clear();
}

std::ostream& sigrid::operator<<(std::ostream &out, const LogicBoard &board)
{
    out << board.m_tileLayer;
    out << board.m_pieceLayer;
    return out;
}
