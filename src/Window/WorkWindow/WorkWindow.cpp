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
    if(m_boards.size() < m_boards.activeDisplayIndex()){
        std::cerr << "WorkWindow: Invalid board id: " << m_boards.activeDisplayIndex() << std::endl;
        return;
    }
    m_boards.atActive().setFilename(filename);
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
    if(m_boards.size() < m_boards.activeDisplayIndex()){
        std::cerr << "WorkWindow: Invalid board id: " << m_boards.activeDisplayIndex() << std::endl;
        return;
    }
    m_boards.atActive().setTileColorManagerPtr(managerPtr);
}

void WorkWindow::setPieceManagerPtr(PieceManager* const managerPtr){
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_boards.size() < m_boards.activeDisplayIndex()){
        std::cerr << "WorkWindow: Invalid board id: " << m_boards.activeDisplayIndex() << std::endl;
        return;
    }
    m_boards.atActive().setPieceManagerPtr(managerPtr);
}

void WorkWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_boards.size() < m_boards.activeDisplayIndex()){
        std::cerr << "WorkWindow: Invalid board id: " << m_boards.activeDisplayIndex() << std::endl;
        return;
    }
    m_boards.atActive().setArrowColorManagerPtr(managerPtr);
}

void WorkWindow::setFontManagerPtr(FontManager* const managerPtr){
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_boards.size() < m_boards.activeDisplayIndex()){
        std::cerr << "WorkWindow: Invalid board id: " << m_boards.activeDisplayIndex() << std::endl;
        return;
    }
    m_boards.atActive().setFontManagerPtr(managerPtr);
}

void WorkWindow::init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    m_boards.atActive().init(boardData, graphicData);

    if(!m_boards.atActive().isImageFilenameSet()){
        m_boards.atActive().setImageFilename(m_defaultBoardImageFilename);
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

        auto& board = m_boards.atDisplay(i);
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
    m_boards.atActive().loadFen(fen);
}

std::string WorkWindow::getName() const{
    if(m_boards.size() == 0){
        return "";
    }
    if(m_boards.size() == 1){
        return m_boards.at(0).getName();
    }
    return m_boards.atActive().getName() + " (" +
        std::to_string(m_boards.activeDisplayIndex()+1) + "/" +
        std::to_string(m_boards.size()) + ")";
}

std::string WorkWindow::getSaveFilename() const{
    return m_boards.atActive().getFilename();
}

std::string WorkWindow::getFen() const{
    return m_boards.atActive().getFen();
}

void WorkWindow::setPosition(const sf::Vector2f& position){
    m_texture.setPosition(position);
}

unsigned int WorkWindow::getNumColumns() const{
    if(m_boards.size() <= m_boards.activeDisplayIndex()){
        return 0;
    }
    return m_boards.atActive().getNumColumns();
}

bool WorkWindow::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}

bool WorkWindow::isCoordinatesOutside() const{
    return m_boards.atActive().isCoordinatesOutside();
}

void WorkWindow::mousePress(const sf::Vector2f& windowPosition){

    m_boards.atActive().removeDragArrow();

    sf::Vector2f position = windowPosition - m_texture.getPosition();

    for(unsigned int displayIndex = 0; displayIndex < m_boards.currentDisplaySize(); displayIndex++){
        auto& board = m_boards.atDisplay(displayIndex);
        if(!board.contains(position)){
            continue;
        }
        if(m_boards.isDisplayActive(displayIndex)){
            m_boards.atActive().deselect();
            m_boards.select(displayIndex);
            updateSelectionHighlight();
        }
        return;
    }
}

Action WorkWindow::clicked(const sigrid::Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& releasePosition){
    
    m_boards.atActive().removeDragArrow();

    sf::Vector2f from = pressPosition - m_texture.getPosition();
    sf::Vector2f to = releasePosition - m_texture.getPosition();

    for(int displayIndex = 0; displayIndex < m_boards.currentDisplaySize(); displayIndex++){
        auto& board = m_boards.atDisplay(displayIndex);

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
        auto& board = m_boards.atDisplay(displayIndex);

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

    BoardDataContainer boardData;
    boardData.load(m_resetBoardFilename);
    m_boards.atActive().loadBoardData(boardData);
}

void WorkWindow::clear(){
    m_boards.atActive().clearEntities();
    m_boards.atActive().clearArrows();
}

void WorkWindow::print(){
    m_boards.atActive().print();
}

void WorkWindow::newBoard(){

    m_boards.atActive().deselect();
    Board newBoard;
    newBoard = m_boards.atActive();

    std::string newName = getUniqueName(m_boards.atActive().getFilename());
    std::string newImageName = getUniqueName(m_boards.atActive().getImageFilename());

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

    m_boards.atActive().deselect();

    m_boards.addColumn();

    updateBoardLayout();

    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::removeBoardColumn(){
    
    auto& currentActiveBoard = m_boards.atActive();

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

    m_boards.atActive().deselect();

    m_boards.addRow();

    updateBoardLayout();

    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::removeBoardRow(){

    auto& currentActiveBoard = m_boards.atActive();

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

    auto& currentActiveBoard = m_boards.atActive();

    if(!m_boards.shiftLeft()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::shiftBoardsRight(){

    auto& currentActiveBoard = m_boards.atActive();

    if(!m_boards.shiftRight()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoRightBoard(){

    auto& currentActiveBoard = m_boards.atActive();

    if(!m_boards.selectRight()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoLeftBoard(){

    auto& currentActiveBoard = m_boards.atActive();

    if(!m_boards.selectLeft()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoUpBoard(){

    auto& currentActiveBoard = m_boards.atActive();

    if(!m_boards.selectUp()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::gotoDownBoard(){

    auto& currentActiveBoard = m_boards.atActive();

    if(!m_boards.selectDown()){
        return;
    }

    currentActiveBoard.deselect();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void WorkWindow::saveBoard(){
    m_boards.atActive().save();
}

void WorkWindow::savePdf(){
    m_pdfHandler.savePdf(m_boards.getVector());
}

void WorkWindow::flipBoard(){
    m_boards.atActive().flipBoard();
}

void WorkWindow::addLeftInsideLabels(){
    m_boards.atActive().addLeftInsideLabels();
}

void WorkWindow::addBottomInsideLabels(){
    m_boards.atActive().addBottomInsideLabels();
}

void WorkWindow::addLeftOutsideLabels(){
    m_boards.atActive().addLeftOutsideLabels();
}

void WorkWindow::addRightOutsideLabels(){
    m_boards.atActive().addRightOutsideLabels();
}

void WorkWindow::addTopOutsideLabels(){
    m_boards.atActive().addTopOutsideLabels();
}

void WorkWindow::addBottomOutsideLabels(){
    m_boards.atActive().addBottomOutsideLabels();
}

void WorkWindow::removeLeftInsideLabels(){
    m_boards.atActive().removeLeftInsideLabels();
}

void WorkWindow::removeBottomInsideLabels(){
    m_boards.atActive().removeBottomInsideLabels();
}

void WorkWindow::removeLeftOutsideLabels(){
    m_boards.atActive().removeLeftOutsideLabels();
}

void WorkWindow::removeRightOutsideLabels(){
    m_boards.atActive().removeRightOutsideLabels();
}

void WorkWindow::removeTopOutsideLabels(){
    m_boards.atActive().removeTopOutsideLabels();
}

void WorkWindow::removeBottomOutsideLabels(){
    m_boards.atActive().removeBottomOutsideLabels();
}

void WorkWindow::setCoordinateSize(const float& size){
    m_boards.atActive().setCoordinateSize(size);    
}

void WorkWindow::addTileColumnRight(){
    m_boards.atActive().addTileColumnRight();
}

void WorkWindow::addTileColumnLeft(){
    m_boards.atActive().addTileColumnLeft();
}

void WorkWindow::removeTileColumnRight(){
    m_boards.atActive().removeTileColumnRight();
}

void WorkWindow::removeTileColumnLeft(){
    m_boards.atActive().removeTileColumnLeft();
}

void WorkWindow::addTileRowUp(){
    m_boards.atActive().addTileRowUp();
}

void WorkWindow::addTileRowDown(){
    m_boards.atActive().addTileRowDown();
}

void WorkWindow::removeTileRowUp(){
    m_boards.atActive().removeTileRowUp();
}

void WorkWindow::removeTileRowDown(){
    m_boards.atActive().removeTileRowDown();
}

void WorkWindow::addBoardBorder(){
    m_boards.atActive().addBorder();
}

void WorkWindow::removeBoardBorder(){
    m_boards.atActive().removeBorder();
}

void WorkWindow::addTurnToken(){
    m_boards.atActive().addTurnToken();
}

void WorkWindow::removeTurnToken(){
    m_boards.atActive().removeTurnToken();
}

void WorkWindow::useAddEntityTool(const Coord& coord, const LogicEntity& newEntity){

    auto occupying_entity_o = m_boards.atActive().getLogicEntity(coord);

    if(occupying_entity_o == std::nullopt){
        m_boards.atActive().addEntity(coord, newEntity);
        return;
    }

    if(occupying_entity_o.value() == newEntity){
        m_boards.atActive().removeEntity(coord);
        return;
    }

    m_boards.atActive().removeEntity(coord);
    m_boards.atActive().addEntity(coord, newEntity);
}

void WorkWindow::useAddEntityAtSelectionTool(const LogicEntity& newEntity){
    m_boards.atActive().addEntityAtSelection(newEntity);
}

void WorkWindow::updateTexture(){

    if(!m_texture.isInitialized()){
        return;
    }

    m_texture.clear();

    for(int i = 0; i < m_boards.currentDisplaySize(); i++){
        m_texture.draw(m_boards.atDisplay(i));
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

    auto tile_o = m_boards.atActive().getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "WorkWindow: unable to find logic tile "
            << coord.getNotation() << " on board with id "
            << m_boards.activeDisplayIndex()
            << " when adding highlight" << std::endl;
        return;
    }

    auto occupyingColor_o = tile_o.value().getHighlightColorId();

    if(occupyingColor_o == std::nullopt){
        m_boards.atActive().addTileHighlight(coord, colorId);
        return;
    }

    if(occupyingColor_o.value() == colorId){
        m_boards.atActive().removeTileHighlight(coord);
        return;
    }

    m_boards.atActive().removeTileHighlight(coord);
    m_boards.atActive().addTileHighlight(coord, colorId);
}

void WorkWindow::useAddArrowTool(const Coord& fromCoord, const Coord& toCoord, const int& colorId){

    auto occupyingArrow_o = m_boards.atActive().getLogicArrow({fromCoord, toCoord});

    if(occupyingArrow_o == std::nullopt){
        m_boards.atActive().addArrow(fromCoord, toCoord, LogicArrow{colorId});
        return;
    }

    if(occupyingArrow_o.value().getColorId() == colorId){
        m_boards.atActive().removeArrow(fromCoord, toCoord);
        return;
    }

    m_boards.atActive().removeArrow(fromCoord, toCoord);
    m_boards.atActive().addArrow(fromCoord, toCoord, LogicArrow{colorId});
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

    const auto& board = m_boards.atActive();
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