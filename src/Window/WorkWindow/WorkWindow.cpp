#include "WorkWindow.h"

#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>

#include "../../Tool/Tool.h"
#include "../../Entity/Tile/GraphicTiles.h"
#include "../../Entity/GraphicEntities.h"
#include "../../Entity/Shape/Arrow/GraphicArrows.h"
#include "../../Board/BoardDataContainer.h"
#include "../../Board/BoardLabels.h"
#include "../../Entity/TurnToken/TurnToken.h"

using namespace sigrid;


WorkWindow::WorkWindow(){
    m_boardSelectHighlight.hide();
    m_boardSelectHighlight.setThickness(10);
    m_boardSelectHighlight.setColor(sf::Color{100,100,255});
}

void WorkWindow::setBoardFilename(const std::string& filename){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.setFilename(filename);
}

void WorkWindow::setResetBoardFilename(const std::string& filename){
    m_resetBoardFilename = filename;
}

void WorkWindow::setDefaultBoardImageFilename(const std::string& filename){
    m_defaultBoardImageFilename = filename;
}

void WorkWindow::setTileColorManagerPtr(ColorManager* const managerPtr){
    
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards.getVector()){
        board.setTileColorManagerPtr(managerPtr);
    }
}

void WorkWindow::setPieceManagerPtr(PieceManager* const managerPtr){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards.getVector()){
        board.setPieceManagerPtr(managerPtr);
    }
}

void WorkWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards.getVector()){
        board.setArrowColorManagerPtr(managerPtr);
    }
}

void WorkWindow::setFontManagerPtr(FontManager* const managerPtr){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards.getVector()){
        board.setFontManagerPtr(managerPtr);
    }
}

void WorkWindow::init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.init(boardData, graphicData);

    if(!board.isImageFilenameSet()){
        board.setImageFilename(m_defaultBoardImageFilename);
    }

    updateBoardLayout();
    m_pdfHandler.updateLayout();
}

void WorkWindow::createGraphic(const sf::Vector2f& size)
{

    int numBoards = m_boards.currentDisplaySize();

    int boardColumns = m_boards.currentDisplayColumns();
    int boardRows = m_boards.currentDisplayRows();

    m_layout.setPx(0, 0.f);
    m_layout.setPy(0, 0.f);

    int maxX = 1+2*boardColumns;

    m_layout.setPx(maxX, size.x);

    int maxY = 1+2*boardRows;
    m_layout.setPy(maxY, size.y);

    bool hasSelectHighlight = numBoards > 1;

    float padding_left = 0.f;
    if(hasSelectHighlight){
        padding_left += m_boardSelectHighlight.getThickness();
    }
    float padding_right = 0.f;
    if(hasSelectHighlight){
        padding_right += m_boardSelectHighlight.getThickness();
    }
    float padding_top = 0.f;
    if(hasSelectHighlight){
        padding_top += m_boardSelectHighlight.getThickness();
    }
    float padding_bottom = 0.f;
    if(hasSelectHighlight){
        padding_bottom += m_boardSelectHighlight.getThickness();
    }
    float padding_betweenX = 20.f;
    float padding_betweenY = 20.f;

    m_layout.setPx(1, padding_left);
    m_layout.setPy(1, padding_bottom);

    m_layout.setPx(maxX-1, size.x - padding_right);
    m_layout.setPy(maxY-1, size.y - padding_top);

    for(int i = 1; i < boardColumns; i++){
        float middleX = padding_left + i*m_layout.getWidth(1,maxX-1).value()/(float)boardColumns;
        m_layout.setPx(2*i, middleX - padding_betweenX/2.f);
        m_layout.setPx(2*i+1, middleX + padding_betweenX/2.f);
    }

    for(int i = 1; i < boardRows; i++){
        float middleY = padding_bottom + i*m_layout.getHeight(1,maxY-1).value()/(float)boardRows;
        m_layout.setPy(2*i, middleY - padding_betweenY/2.f);
        m_layout.setPy(2*i+1, middleY + padding_betweenY/2.f);
    }

    m_texture.setSize(size);

    for(LayoutItem i = 0; i < numBoards; i++){
        auto layoutBoardSize_o = m_layout.getSize(LayoutItem{i});
        if(layoutBoardSize_o == std::nullopt){
            std::cerr << "WorkWindow: createGraphic failed, failed getting boardLayoutSize" << std::endl;
            return;
        }
        float layoutBoardWidth = layoutBoardSize_o.value().x;
        float layoutBoardHeight = layoutBoardSize_o.value().y;
        auto boardTopLeftPosition_o = m_layout.getTopLeftPosition(LayoutItem{i});
        if(boardTopLeftPosition_o == std::nullopt){
            std::cerr << "WorkWindow: createGraphic failed, failed getting boardLayoutPosition" << std::endl;
            return;
        }
        sf::Vector2f boardTopLeftPosition = boardTopLeftPosition_o.value();

        auto board_o = m_boards.atDisplay(i);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();
        unsigned int boardWidth = board.getImageWidth();
        unsigned int boardHeight = board.getImageHeight();
        float widthRatio = layoutBoardWidth/(float)boardWidth;
        float heightRatio = layoutBoardHeight/(float)boardHeight;
        float boardScale;
        if(widthRatio < heightRatio){
            boardScale = widthRatio;
        }
        else{
            boardScale = heightRatio;
        }
        board.setScale(boardScale);

        float posX = boardTopLeftPosition.x + (layoutBoardWidth - board.getDisplayWidth())/2.f;
        float posY = boardTopLeftPosition.y + (layoutBoardHeight - board.getDisplayHeight())/2.f;

        board.setPosition({posX, posY});
    }

    updateSelectionHighlight();
    updateTexture();
}

void WorkWindow::loadFen(const std::string& fen){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.loadFen(fen);
}

std::string WorkWindow::getName() const{

    if(m_boards.size() == 0){
        return "";
    }
    if(m_boards.size() == 1){
        auto board_o = m_boards.at(0);
        if(board_o == std::nullopt){
            return "";
        }
        auto& board = board_o.value().get();
        return board.getName();
    }

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return "";
    }
    auto& board = board_o.value().get();

    return board.getName() + " (" +
        std::to_string(m_boards.activeDisplayIndex().value()+1) + "/" +
        std::to_string(m_boards.size()) + ")";
}

std::string WorkWindow::getSaveFilename() const{

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return "";
    }
    auto& board = board_o.value().get();

    return board.getFilename();
}

std::string WorkWindow::getFen() const{

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return "";
    }
    auto& board = board_o.value().get();

    return board.getFen();
}

void WorkWindow::setPosition(const sf::Vector2f& position){
    m_texture.setPosition(position);
}

unsigned int WorkWindow::getNumColumns() const{

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return 0;
    }
    auto& board = board_o.value().get();

    if(m_boards.size() <= m_boards.activeDisplayIndex()){
        return 0;
    }
    return board.getNumColumns();
}

bool WorkWindow::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}

bool WorkWindow::isCoordinatesOutside() const{

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return false;
    }
    auto& board = board_o.value().get();

    return board.isCoordinatesOutside();
}

void WorkWindow::mousePress(const sf::Vector2f& windowPosition){

    auto activeBoard_o = m_boards.atSelection();

    if(activeBoard_o){
        activeBoard_o.value().get().removeDragArrow();
    }

    sf::Vector2f position = windowPosition - m_texture.getPosition();

    for(unsigned int displayIndex = 0; displayIndex < m_boards.currentDisplaySize(); displayIndex++){
        
        auto board_o = m_boards.atDisplay(displayIndex);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();
        
        if(!board.contains(position)){
            continue;
        }
        if(m_boards.isDisplayActive(displayIndex)){
            if(activeBoard_o){
                activeBoard_o.value().get().deselect();
            }
            m_boards.select(displayIndex);
            updateSelectionHighlight();
        }
        return;
    }
}

Action WorkWindow::clicked(const sigrid::Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& releasePosition){
    
    auto activeBoard_o = m_boards.atSelection();

    if(activeBoard_o){
        activeBoard_o.value().get().removeDragArrow();
    }

    sf::Vector2f from = pressPosition - m_texture.getPosition();
    sf::Vector2f to = releasePosition - m_texture.getPosition();

    for(int displayIndex = 0; displayIndex < m_boards.currentDisplaySize(); displayIndex++){
        
        auto board_o = m_boards.atDisplay(displayIndex);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();
        
        if(board.isWithinTurnToken(from) &&
        board.isWithinTurnToken(to)){
            board.toggleTurnToken();
            return ActionType::None();
        }

        auto fromCoord_o = board.getTileCoord(from);

        if(fromCoord_o == std::nullopt){
            continue;
        }

        auto toCoord_o = board.getTileCoord(to);

        if(toCoord_o == std::nullopt){
            switch(tool.selection()){
                case ToolSelection::Select:
                    board.deselect();
                    break;
                default:
                    break;
            }
            return ActionType::None();
        }

        auto fromCoord = fromCoord_o.value();
        auto toCoord = toCoord_o.value();

        switch(tool.selection()){
            case ToolSelection::Select:
                if(fromCoord == toCoord){
                    board.select(toCoord);
                }
                else{
                    board.dragAndDrop(fromCoord_o.value(), toCoord_o.value());
                }
                return ActionType::None();
            case ToolSelection::EntityAdder:
                useAddEntityTool(toCoord,tool.getEntity());
                return ActionType::None();
            case ToolSelection::EntityPicker:
                {
                    auto logicEntity_o = board.getLogicEntity(toCoord);
                    if(logicEntity_o == std::nullopt){
                        return ActionType::None();
                    }
                    ActionType::PickEntity action{logicEntity_o.value()};
                    return action;
                }
            case ToolSelection::DrawArrow:
                if(fromCoord == toCoord){
                    useAddTileHighlightTool(toCoord, tool.getArrowColorId());
                    return ActionType::None();
                }
                useAddArrowTool(fromCoord, toCoord, tool.getArrowColorId());
                return ActionType::None();
            default:
                return ActionType::None();
        }
    }
    return ActionType::None();
}

void WorkWindow::dragMouse(const Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& currentPosition){
    
    sf::Vector2f from = pressPosition - m_texture.getPosition();
    sf::Vector2f to = currentPosition - m_texture.getPosition();

    for(int displayIndex = 0; displayIndex < m_boards.currentDisplaySize(); displayIndex++){
        
        auto board_o = m_boards.atDisplay(displayIndex);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();
        
        auto fromCoord_o = board.getTileCoord(from);

        if(fromCoord_o == std::nullopt){
            continue;
        }

        auto toCoord_o = board.getTileCoord(to);

        if(toCoord_o == std::nullopt){
            board.removeDragArrow();
            return;
        }

        auto fromCoord = fromCoord_o.value();
        auto toCoord = toCoord_o.value();

        if(fromCoord == toCoord){
            board.removeDragArrow();
            return;
        }

        switch(tool.selection()){
            case ToolSelection::Select:
                if(!board.isEmptyTile(fromCoord)){
                    board.updateDragArrow(fromCoord, toCoord, tool.getArrowColorId());
                }
                return;
            case ToolSelection::DrawArrow:
                board.updateDragArrow(fromCoord, toCoord, tool.getArrowColorId());
                return;
            default:
                return;
        }
        return;
    }
}

void WorkWindow::reset(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    BoardDataContainer boardData;
    boardData.load(m_resetBoardFilename);
    board.loadBoardData(boardData);
}

void WorkWindow::clear(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.clearEntities();
    board.clearArrows();
}

void WorkWindow::print(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.print();
}

void WorkWindow::newBoard(){

    auto activeBoard_o = m_boards.atSelection();

    if(activeBoard_o){
        activeBoard_o.value().get().deselect();
    }
    Board newBoard;
    if(activeBoard_o){
        newBoard = activeBoard_o.value().get();
    }

    std::string newName = getUniqueName(newBoard.getFilename());
    std::string newImageName = getUniqueName(newBoard.getImageFilename());

    std::cout << "New board name " << newName << std::endl;
    std::cout << "New image name " << newImageName << std::endl;    
    
    newBoard.setFilename(newName);
    newBoard.setImageFilename(newImageName);

    m_boards.push_back(std::move(newBoard));
    m_boards.selectLast();

    reset();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::addBoardColumn(){

    auto activeBoard_o = m_boards.atSelection();
    if(activeBoard_o){
        activeBoard_o.value().get().deselect();
    }

    m_boards.addColumn();

    updateBoardLayout();

    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::removeBoardColumn(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.removeColumn()){
        return;
    }

    currentActiveBoard.deselect();

    updateBoardLayout();

    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::addBoardRow(){

    auto activeBoard_o = m_boards.atSelection();
    if(activeBoard_o){
        activeBoard_o.value().get().deselect();
    }

    m_boards.addRow();

    updateBoardLayout();

    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::removeBoardRow(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.removeRow()){
        return;
    }

    currentActiveBoard.deselect();

    updateBoardLayout();

    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::shiftBoardsLeft(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.shiftLeft()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::shiftBoardsRight(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.shiftRight()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoRightBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.selectRight()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoLeftBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.selectLeft()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoUpBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.selectUp()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoDownBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& currentActiveBoard = board_o.value().get();

    if(!m_boards.selectDown()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::saveBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.save();
}

void WorkWindow::savePdf(){
    m_pdfHandler.savePdf(m_boards.getVector());
}

void WorkWindow::flipBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.flipBoard();
}

void WorkWindow::addLeftInsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addLeftInsideLabels();
}

void WorkWindow::addBottomInsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addBottomInsideLabels();
}

void WorkWindow::addLeftOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addLeftOutsideLabels();
}

void WorkWindow::addRightOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addRightOutsideLabels();
}

void WorkWindow::addTopOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTopOutsideLabels();
}

void WorkWindow::addBottomOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addBottomOutsideLabels();
}

void WorkWindow::removeLeftInsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeLeftInsideLabels();
}

void WorkWindow::removeBottomInsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeBottomInsideLabels();
}

void WorkWindow::removeLeftOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeLeftOutsideLabels();
}

void WorkWindow::removeRightOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeRightOutsideLabels();
}

void WorkWindow::removeTopOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeTopOutsideLabels();
}

void WorkWindow::removeBottomOutsideLabels(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeBottomOutsideLabels();
}

void WorkWindow::setCoordinateSize(const float& size){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.setCoordinateSize(size);    
}

void WorkWindow::addTileColumnRight(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileColumnRight();
}

void WorkWindow::addTileColumnLeft(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileColumnLeft();
}

void WorkWindow::removeTileColumnRight(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeTileColumnRight();
}

void WorkWindow::removeTileColumnLeft(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeTileColumnLeft();
}

void WorkWindow::addTileRowUp(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileRowUp();
}

void WorkWindow::addTileRowDown(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileRowDown();
}

void WorkWindow::removeTileRowUp(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeTileRowUp();
}

void WorkWindow::removeTileRowDown(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeTileRowDown();
}

void WorkWindow::addBoardBorder(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addBorder();
}

void WorkWindow::removeBoardBorder(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeBorder();
}

void WorkWindow::addTurnToken(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTurnToken();
}

void WorkWindow::removeTurnToken(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeTurnToken();
}

void WorkWindow::useAddEntityTool(const Coord& coord, const LogicEntity& newEntity){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    auto occupying_entity_o = board.getLogicEntity(coord);

    if(occupying_entity_o == std::nullopt){
        board.addEntity(coord, newEntity);
        return;
    }

    if(occupying_entity_o.value() == newEntity){
        board.removeEntity(coord);
        return;
    }

    board.removeEntity(coord);
    board.addEntity(coord, newEntity);
}

void WorkWindow::useAddEntityAtSelectionTool(const LogicEntity& newEntity){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addEntityAtSelection(newEntity);
}

void WorkWindow::updateTexture(){

    if(!m_texture.isInitialized()){
        return;
    }

    m_texture.clear();

    for(int i = 0; i < m_boards.currentDisplaySize(); i++){

        auto board_o = m_boards.atDisplay(i);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();

        m_texture.draw(board);
    }
    m_texture.draw(m_boardSelectHighlight);

    m_texture.display();
}

std::string WorkWindow::getUniqueName(const std::string& name){
    std::string newName(name);
    while(true){
        
        bool exists = false;
        for(const auto& board: m_boards.getVector()){
            if(board.getFilename() == newName || board.getImageFilename() == newName){
                exists = true;
                break;
            }
        }
        if(!exists){
            if(!std::filesystem::exists(newName)){
                break;
            }
        }

        auto endPos = newName.rfind('.');
        if(endPos == newName.npos){
            std::cerr << "WorkWindow: No . in getUniqueName";
            return newName;
        }
        auto startPos = endPos;
        while(std::isdigit(newName.at(startPos-1))){
            startPos--;
        }
        if(startPos == endPos){
            newName.insert(startPos, "2");
        }
        else{
            std::string digitString = newName.substr(startPos,endPos-startPos);
            int digit = std::stoi(digitString);
            digit++;
            digitString = std::to_string(digit);
            newName.erase(startPos,endPos-startPos);
            newName.insert(startPos, digitString);
        }
    }
    return newName;
}

void WorkWindow::useAddTileHighlightTool(const Coord& coord, const int& colorId){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    auto tile_o = board.getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "WorkWindow: unable to find logic tile "
            << coord.getNotation() << " on board with id "
            << m_boards.activeDisplayIndex().value()
            << " when adding highlight" << std::endl;
        return;
    }

    auto occupyingColor_o = tile_o.value().getHighlightColorId();

    if(occupyingColor_o == std::nullopt){
        board.addTileHighlight(coord, colorId);
        return;
    }

    if(occupyingColor_o.value() == colorId){
        board.removeTileHighlight(coord);
        return;
    }

    board.removeTileHighlight(coord);
    board.addTileHighlight(coord, colorId);
}

void WorkWindow::useAddArrowTool(const Coord& fromCoord, const Coord& toCoord, const int& colorId){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    auto occupyingArrow_o = board.getLogicArrow({fromCoord, toCoord});

    if(occupyingArrow_o == std::nullopt){
        board.addArrow(fromCoord, toCoord, LogicArrow{colorId});
        return;
    }

    if(occupyingArrow_o.value().getColorId() == colorId){
        board.removeArrow(fromCoord, toCoord);
        return;
    }

    board.removeArrow(fromCoord, toCoord);
    board.addArrow(fromCoord, toCoord, LogicArrow{colorId});
}

void WorkWindow::updateBoardLayout(){

    unsigned int i = 0;
    for(unsigned int y = 0; y < m_boards.maxDisplayRows(); y++){
        for(unsigned int x = 0; x < m_boards.maxDisplayColumns(); x++){
            m_layout.setFromXCoord(LayoutItem{i}, 1 + 2*x);
            m_layout.setToXCoord(LayoutItem{i}, 2 + 2*x);
            m_layout.setFromYCoord(LayoutItem{i}, 1 + 2*y);
            m_layout.setToYCoord(LayoutItem{i}, 2 + 2*y);
            i++;
        }
    }
}

void WorkWindow::updateSelectionHighlight(){

    if(m_boards.currentDisplaySize() < 2){
        m_boardSelectHighlight.hide();
        return;
    }

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    const float& thickness = m_boardSelectHighlight.getThickness();
    sf::Vector2f position = board.getTopLeftPosition();
    position -= sf::Vector2f{thickness, thickness};
    m_boardSelectHighlight.setTopLeftPosition(position);
    m_boardSelectHighlight.setEnclosedArea(board.getDisplaySize());
    m_boardSelectHighlight.show();
}

void WorkWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_texture.isInitialized()){
        return;
    }

    target.draw(m_texture);
}