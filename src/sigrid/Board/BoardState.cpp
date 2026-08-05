#include "sigrid/Board/BoardState.h"

#include "sigrid/Board/BoardStateContainer.h"

#include <iostream>

using namespace sigrid;

bool BoardState::load(const BoardStateContainer& data){

    m_tileLayer.clear();
    m_pieceLayer.clear();
    m_arrowLayer.clear();
    m_turnToMove = 0;

    if(data.repeatTileColorIds.size() == 0){
        std::cerr << "BoardState: Failed to setup LogicBoard: Default tile colors not set" << std::endl;
        return false;
    }

    m_tileLayer.setNumColumns(data.columns);
    m_tileLayer.setNumRows(data.rows);
    m_tileLayer.setInsertPattern(data.repeatTileColorIds);
    m_tileLayer.insertAllTiles();

    for(const auto pieceContainer : data.logicPieces){

        sigrid_coord::Coord coord{pieceContainer.position};

        if(coord.y < 0){
            std::cerr << "BoardState: Failed to set piece at " << coord.getNotation() << ", missing row on board" << std::endl;
            continue;
        }
        if(coord.y >= getNumRows()){
            std::cerr << "BoardState: Failed to set piece at " << coord.getNotation() << ", missing row on board" << std::endl;
            continue;
        }
        if(coord.x < 0){
            std::cerr << "BoardState: Failed to set piece at " << coord.getNotation() << ", missing column on board" << std::endl;
            continue;
        }
        if(coord.x >= getNumColumns()){
            std::cerr << "BoardState: Failed to set piece at " << coord.getNotation() << ", missing column on board" << std::endl;
            continue;
        }
        LogicPiece logicPiece;
        logicPiece.setNotation(pieceContainer.name);
        logicPiece.setColorId(pieceContainer.colorId);
        m_pieceLayer.addEntity(coord, std::move(logicPiece));
    }

    for(const auto cData : data.logicCircles){

        sigrid_coord::Coord coord{cData.position};

        if(!isWithinBoard(coord)){
            std::cerr << "LogicBoard constructor: Failed to set circle at " << coord.getNotation() << std::endl;
            std::cerr << "coordinate is outside of board" << std::endl;
            continue;
        }

        LogicCircle logicCircle;
        logicCircle.setColor(cData.colorId);
        m_pieceLayer.addEntity(coord, std::move(logicCircle));
    }

    for(const auto arrowData : data.logicArrows){

        sigrid_coord::CoordPair coordPair{arrowData.position};

        if(!isWithinBoard(coordPair.from)){
            std::cerr << "LogicBoard constructor: Failed to set arrow at " << coordPair.getNotation() << std::endl;
            std::cerr << "Starting coordinate is outside of board" << std::endl;
            continue;
        }

        if(!isWithinBoard(coordPair.to)){
            std::cerr << "LogicBoard constructor: Failed to set arrow at " << coordPair.getNotation() << std::endl;
            std::cerr << "End coordinate is outside of board" << std::endl;
            continue;
        }

        LogicArrow logicArrow;
        logicArrow.setColor(arrowData.colorId);
        m_arrowLayer.addArrow(coordPair, std::move(logicArrow));
    }

    return true;
}

const int BoardState::getNumColumns() const{
    return m_tileLayer.getNumColumns();
}

const int BoardState::getNumRows() const{
    return m_tileLayer.getNumRows();
}

bool BoardState::isWithinBoard(const sigrid_coord::Coord& coord) const{
    if(coord.x >= getNumColumns()){
        return false;
    }
    if(coord.y >= getNumRows()){
        return false;
    }
    return true;
}

bool BoardState::isEmptyTile(const sigrid_coord::Coord& coord) const{
    if(!isWithinBoard(coord)){
        return false;
    }
    return m_pieceLayer.getEntityAt(coord) == std::nullopt;
}

std::optional<LogicTile> BoardState::getTile(const sigrid_coord::Coord& coord) const{

    auto tile_o = m_tileLayer.getTile(coord);

    if(tile_o == std::nullopt){
        return std::nullopt;
    }

    return tile_o.value();
}

std::optional<LogicEntity> BoardState::getEntityAt(const sigrid_coord::Coord& coord) const{
    return m_pieceLayer.getEntityAt(coord);
}

std::optional<LogicArrow> BoardState::getArrowAtIndex(const int& index) const{

    auto arrow_o = m_arrowLayer.getArrowAtIndex(index);

    if(arrow_o == std::nullopt){
        return std::nullopt;
    }
    return arrow_o.value();
}

std::optional<sigrid_coord::CoordPair> BoardState::getArrowKeyAtIndex(const int& index) const{

    auto coordPair_o = m_arrowLayer.getArrowKeyAtIndex(index);

    if(coordPair_o == std::nullopt){
        return std::nullopt;
    }
    return coordPair_o.value();
}

std::optional<LogicArrow> BoardState::getArrowAt(const sigrid_coord::CoordPair& coordPair) const{

    auto arrow_o = m_arrowLayer.getArrow(coordPair);

    if(arrow_o == std::nullopt){
        return std::nullopt;
    }

    return arrow_o.value();
}

sigrid::String BoardState::getFen() const{

    sigrid::String fen;

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

                std::string stdString = std::to_string(i);
                sigrid::String sigridString;
                sigridString.set(std::move(stdString));

                fen.append(sigridString);
                i = 0;
            }
            LogicPiece piece = std::get<LogicPiece>(entity_o.value());
            sigrid::String s = piece.getNotation();
            if(piece.getColorId() == 1){
                s.toLower();
            }
            fen.append(s);
            
        }
        if(i > 0){

            std::string stdString = std::to_string(i);
            sigrid::String sigridString;
            sigridString.set(std::move(stdString));

            fen.append(sigridString);
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

int BoardState::getTurnToMove() const{
    return m_turnToMove;
}

sigrid_list::Vector<int> BoardState::getRepeatColorIds() const{
    return m_tileLayer.getRepeatColorIds();
}

int BoardState::getNumArrows() const{
    return m_arrowLayer.size();
}

void BoardState::setTurnToMove(const int& turnToMove){
    m_turnToMove = turnToMove;
}

bool BoardState::addEntity(const sigrid_coord::Coord& coord, const LogicEntity& entity){

    if(!isWithinBoard(coord)){
        std::cerr << "BoardState: Unable to add entity at " << coord.getNotation() << std::endl;
        std::cerr << "The tile is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.getEntityAt(coord) != std::nullopt){
        std::cerr << "BoardState: Unable to add entity at " << coord.getNotation() << std::endl;
        std::cerr << "The tile is already occupied" << std::endl;
        return false;
    }

    m_pieceLayer.addEntity(coord,entity);
    return true;
}

bool BoardState::removeEntity(const sigrid_coord::Coord& coord){

    if(!isWithinBoard(coord)){
        std::cerr << "BoardState: Unable to remove entity at " << coord.getNotation() << std::endl;
        std::cerr << "The tile is outside of the board" << std::endl;
        return false;
    }

    if(m_pieceLayer.getEntityAt(coord) == std::nullopt){
        std::cerr << "BoardState: Unable to remove entity at " << coord.getNotation() << std::endl;
        std::cerr << "There is no entity there" << std::endl;
        return false;
    }

    m_pieceLayer.removeEntity(coord);
    return true;
}

bool BoardState::moveEntity(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord){

    if(fromCoord.x == toCoord.x && fromCoord.y == toCoord.y){
        std::cerr << "BoardState: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cerr << "both coordinates are the same" << std::endl;
        return false;
    }

    if(!isWithinBoard(fromCoord)){
        std::cerr << "BoardState: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cerr << "starting tile is out of bounds" << std::endl;
        return false;
    }

    if(!isWithinBoard(toCoord)){
        std::cerr << "BoardState: Unable to move entity from " << fromCoord.getNotation()
            << " to " << toCoord.getNotation() << std::endl;
        std::cerr << "destination tile is out of bounds" << std::endl;
        return false;
    }

    if(isEmptyTile(fromCoord)){
        std::cerr << "BoardState: Unable to move entity from " << fromCoord.getNotation() << std::endl;
        std::cerr << "No piece is standing there" << std::endl;
        return false;
    }

    if(!isEmptyTile(toCoord)){
        m_pieceLayer.removeEntity(toCoord);
    }

    m_pieceLayer.moveEntity(fromCoord, toCoord);
    return true;
}

bool BoardState::addTileHighlight(const sigrid_coord::Coord& coord, const int& highlightColorId){

    if(highlightColorId < 0){
        std::cerr << "BoardState: Unable to add highlight." << std::endl;
        std::cerr << "ColorId is not set (value: " << highlightColorId << ")" << std::endl;
        return false;
    }

    auto tile_o = m_tileLayer.getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "BoardState: Unable to add highlight." << std::endl;
        std::cerr << "Coord is not a valid tile (value:" << coord.getNotation() << ")" << std::endl;
        return false;
    }

    m_tileLayer.setHighlightColor(coord, highlightColorId);
    return true;
}

bool BoardState::removeTileHighlight(const sigrid_coord::Coord& coord){

    auto tile_o = m_tileLayer.getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "BoardState: Unable to add highlight." << std::endl;
        std::cerr << "Coord is not a valid tile (value:" << coord.getNotation() << ")" << std::endl;
        return false;
    }

    m_tileLayer.removeHighlight(coord);
    return true;
}

bool BoardState::addArrow(const sigrid_coord::CoordPair& coordPair, const LogicArrow& arrow){

    if(!isWithinBoard(coordPair.from)){
        std::cerr << "BoardState: Unable to add arrow from tile: " << coordPair.from.getNotation() << std::endl;
        std::cerr << "Starting tile is outside of the board" << std::endl;
        return false;
    }

    if(!isWithinBoard(coordPair.to)){
        std::cerr << "BoardState: Unable to add arrow to tile: " << coordPair.to.getNotation() << std::endl;
        std::cerr << "Destination tile is outside of the board" << std::endl;
        return false;
    }

    if(arrow.getColorId() < 0){
        std::cerr << "BoardState: Unable to add arrow" << std::endl;
        std::cerr << "ColorId is not set (value: " << arrow.getColorId() << ")" << std::endl;
        return false;
    }

    auto occupyingArrow_o = m_arrowLayer.getArrow(coordPair);

    if(occupyingArrow_o != std::nullopt){
        std::cerr << "BoardState: Unable to add arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "There is already an arrow there" << std::endl;
        return false;
    }

    m_arrowLayer.addArrow(coordPair, arrow);
    return true;
}


bool BoardState::removeArrow(const sigrid_coord::CoordPair& coordPair){

    auto occupyingArrow_o = m_arrowLayer.getArrow(coordPair);

    if(occupyingArrow_o == std::nullopt){
        std::cerr << "BoardState: Unable to remove arrow at "
            << coordPair.getNotation() << std::endl;
        std::cerr << "There is no arrow there" << std::endl;
        return false;
    }

    m_arrowLayer.removeArrow(coordPair);
    return true;
}

bool BoardState::addTileColumnRight(){
    return m_tileLayer.addColumnRight();
}

bool BoardState::addTileColumnLeft(){
    if(!m_tileLayer.addColumnLeft()){
        return false;
    }
    m_pieceLayer.moveEntitiesRight();
    m_arrowLayer.moveArrowsRight();
    return true;
}

bool BoardState::removeRightTileColumn(){
    if(!m_tileLayer.removeRightColumn()){
        return false;
    }
    int columnId = m_tileLayer.getNumColumns();
    m_pieceLayer.removeColumn(columnId);
    m_arrowLayer.removeColumn(columnId);
    return true;
}

bool BoardState::removeLeftTileColumn(){
    if(!m_tileLayer.removeLeftColumn()){
        return false;
    }
    m_pieceLayer.removeColumn(0);
    m_pieceLayer.moveEntitiesLeft();
    m_arrowLayer.removeColumn(0);
    m_arrowLayer.moveArrowsLeft();
    return true;
}

bool BoardState::addTileRowUp(){
    if(!m_tileLayer.addRowUp()){
        return false;
    }
    m_pieceLayer.moveEntitiesDown();
    m_arrowLayer.moveArrowsDown();
    return true;
}

bool BoardState::addTileRowDown(){
    return m_tileLayer.addRowDown();
}

bool BoardState::removeTopTileRow(){
    if(!m_tileLayer.removeTopRow()){
        return false;
    }
    m_pieceLayer.removeRow(0);
    m_pieceLayer.moveEntitiesUp();
    m_arrowLayer.removeRow(0);
    m_arrowLayer.moveArrowsUp();
    return true;
}

bool BoardState::removeBottomTileRow(){
    if(!m_tileLayer.removeBottomRow()){
        return false;
    }
    int rowId = m_tileLayer.getNumRows();
    m_pieceLayer.removeRow(rowId);
    m_arrowLayer.removeRow(rowId);
    return true;
}

void BoardState::print(){
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

void BoardState::clearEntities(){
    m_pieceLayer.clear();
}

void BoardState::clearArrows(){
    m_arrowLayer.clear();
}

std::ostream& sigrid::operator<<(std::ostream &out, const BoardState &board)
{
    out << board.m_tileLayer;
    out << board.m_pieceLayer;
    out << board.m_arrowLayer;
    return out;
}
