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


WorkWindow::WorkWindow()
: m_activeBoardIndex{0}
, m_displayBoardIds{{0}}{
    m_boardSelectHighlight.hide();
    m_boardSelectHighlight.setThickness(10);
    m_boardSelectHighlight.setColor(sf::Color{100,100,255});
}

void WorkWindow::setBoardFilename(const std::string& filename){
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_boards.size() < activeId()){
        std::cerr << "WorkWindow: Invalid board id: " << activeId() << std::endl;
        return;
    }
    activeBoard().setFilename(filename);
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
    if(m_boards.size() < activeId()){
        std::cerr << "WorkWindow: Invalid board id: " << activeId() << std::endl;
        return;
    }
    activeBoard().setTileColorManagerPtr(managerPtr);
}

void WorkWindow::setPieceManagerPtr(PieceManager* const managerPtr){
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_boards.size() < activeId()){
        std::cerr << "WorkWindow: Invalid board id: " << activeId() << std::endl;
        return;
    }
    activeBoard().setPieceManagerPtr(managerPtr);
}

void WorkWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_boards.size() < activeId()){
        std::cerr << "WorkWindow: Invalid board id: " << activeId() << std::endl;
        return;
    }
    activeBoard().setArrowColorManagerPtr(managerPtr);
}

void WorkWindow::setFontManagerPtr(FontManager* const managerPtr){
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_boards.size() < activeId()){
        std::cerr << "WorkWindow: Invalid board id: " << activeId() << std::endl;
        return;
    }
    activeBoard().setFontManagerPtr(managerPtr);
}

void WorkWindow::init(const BoardDataContainer& boardData, const BoardDesignContainer& graphicData){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }
    if(m_displayBoardIds.size() == 0){
        m_displayBoardIds.push_back(0);
    }
    m_activeBoardIndex = 0;

    activeBoard().init(boardData, graphicData);

    if(!activeBoard().isImageFilenameSet()){
        activeBoard().setImageFilename(m_defaultBoardImageFilename);
    }

    updateBoardLayout();
    m_pdfHandler.updateLayout();
}

void WorkWindow::createGraphic(const sf::Vector2f& size)
{

    int numBoards = m_displayBoardIds.size();

    int boardColumns = (numBoards > m_maxBoardColumns) ? m_maxBoardColumns : numBoards;
    int boardRows = (numBoards + boardColumns - 1)/boardColumns;

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

    for(LayoutItem i = 0; i < m_displayBoardIds.size(); i++){
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

        auto& board = m_boards.at(m_displayBoardIds.at(i));
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
    activeBoard().loadFen(fen);
}

std::string WorkWindow::getName() const{
    if(m_boards.size() == 0){
        return "";
    }
    if(m_boards.size() == 1){
        return m_boards.at(0).getName();
    }
    return activeBoard().getName() + " (" +
        std::to_string(activeId()+1) + "/" +
        std::to_string(m_boards.size()) + ")";
}

std::string WorkWindow::getSaveFilename() const{
    return activeBoard().getFilename();
}

std::string WorkWindow::getFen() const{
    return activeBoard().getFen();
}

void WorkWindow::setPosition(const sf::Vector2f& position){
    m_texture.setPosition(position);
}

unsigned int WorkWindow::getNumColumns() const{
    if(m_boards.size() <= activeId()){
        return 0;
    }
    return activeBoard().getNumColumns();
}

bool WorkWindow::contains(const sf::Vector2f& point) const{
    return m_texture.contains(point);
}

bool WorkWindow::isCoordinatesOutside() const{
    return activeBoard().isCoordinatesOutside();
}

void WorkWindow::mousePress(const sf::Vector2f& windowPosition){

    activeBoard().removeDragArrow();

    sf::Vector2f position = windowPosition - m_texture.getPosition();

    for(unsigned int displayIndex = 0; displayIndex < m_displayBoardIds.size(); displayIndex++){
        auto& board = m_boards.at(m_displayBoardIds.at(displayIndex));
        if(!board.contains(position)){
            continue;
        }
        if(m_activeBoardIndex != displayIndex){
            activeBoard().deselect();
            m_activeBoardIndex = displayIndex;
            updateSelectionHighlight();
        }
        return;
    }
}

Action WorkWindow::clicked(const sigrid::Tool& tool, const sf::Vector2f& pressPosition, const sf::Vector2f& releasePosition){
    
    activeBoard().removeDragArrow();

    sf::Vector2f from = pressPosition - m_texture.getPosition();
    sf::Vector2f to = releasePosition - m_texture.getPosition();

    for(int displayIndex = 0; displayIndex < m_displayBoardIds.size(); displayIndex++){
        auto& board = m_boards.at(m_displayBoardIds.at(displayIndex));

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

    for(int displayIndex = 0; displayIndex < m_displayBoardIds.size(); displayIndex++){
        auto& board = m_boards.at(m_displayBoardIds.at(displayIndex));

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
    activeBoard().loadBoardData(boardData);
}

void WorkWindow::clear(){
    activeBoard().clearEntities();
    activeBoard().clearArrows();
}

void WorkWindow::print(){
    activeBoard().print();
}

void WorkWindow::newBoard(){

    activeBoard().deselect();
    Board newBoard;
    newBoard = activeBoard();

    std::string newName = getUniqueName(activeBoard().getFilename());
    std::string newImageName = getUniqueName(activeBoard().getImageFilename());

    std::cout << "New board name " << newName << std::endl;
    std::cout << "New image name " << newImageName << std::endl;    
    
    newBoard.setFilename(newName);
    newBoard.setImageFilename(newImageName);

    m_boards.push_back(std::move(newBoard));

    if(m_displayBoardIds.size() < m_maxBoardColumns*m_maxBoardRows){
        m_displayBoardIds.push_back(m_boards.size()-1);
    }
    else{
        displayLastBoards();
    }
    
    m_activeBoardIndex = m_displayBoardIds.size()-1;

    reset();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::addBoardColumn(){

    activeBoard().deselect();

    m_maxBoardColumns++;

    updateBoardLayout();
    displayLastBoards();

    m_activeBoardIndex = m_displayBoardIds.size()-1;

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::removeBoardColumn(){
    
    if(m_maxBoardColumns < 2){
        return;
    }

    activeBoard().deselect();

    m_maxBoardColumns--;

    updateBoardLayout();
    displayLastBoards();

    m_activeBoardIndex = m_displayBoardIds.size()-1;

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::addBoardRow(){

    activeBoard().deselect();

    m_maxBoardRows++;

    updateBoardLayout();
    displayLastBoards();

    m_activeBoardIndex = m_displayBoardIds.size()-1;

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::removeBoardRow(){

    if(m_maxBoardRows < 2){
        return;
    }

    activeBoard().deselect();

    m_maxBoardRows--;

    updateBoardLayout();
    displayLastBoards();

    m_activeBoardIndex = m_displayBoardIds.size()-1;

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::shiftBoardsLeft(){

    if(m_boards.size() < 2){
        return;
    }

    activeBoard().deselect();

    if(m_displayBoardIds.size() == m_boards.size()
    || m_activeBoardIndex % m_maxBoardColumns != 0){

        m_activeBoardIndex = (m_displayBoardIds.size() + m_activeBoardIndex - 1)%m_displayBoardIds.size();

        if(m_texture.isInitialized()){
            createGraphic(m_texture.getSize());
        }
        return;
    }

    for(int i = 0; i < m_displayBoardIds.size()-1; i++){
        m_displayBoardIds.at(i) = m_displayBoardIds.at(i+1);
    }

    auto isDisplayed = [this](const int& id){
        for(int i = 0; i < m_displayBoardIds.size()-1; i++){
            if(m_displayBoardIds.at(i) == id){
                return true;
            }
        }
        return false;
    };

    {
        int backId = m_displayBoardIds.back();
        if(backId == 0){
            backId = m_boards.size()-1;
        }
        else{
            backId--;
        }
        while(backId != m_displayBoardIds.back()){
            if(!isDisplayed(backId)){
                m_displayBoardIds.back() = backId;
                break;
            }

            if(backId == 0){
                backId = m_boards.size()-1;
            }
            else{
                backId--;
            }
        }
    }

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::shiftBoardsRight(){

    if(m_boards.size() < 2){
        return;
    }

    activeBoard().deselect();

    if(m_displayBoardIds.size() == m_boards.size()
    || m_activeBoardIndex % m_maxBoardColumns != m_maxBoardColumns - 1){

        m_activeBoardIndex = (m_activeBoardIndex + 1)%m_displayBoardIds.size();

        if(m_texture.isInitialized()){
            createGraphic(m_texture.getSize());
        }
        return;
    }

    for(int i = m_displayBoardIds.size()-1; i > 0; i--){
        m_displayBoardIds.at(i) = m_displayBoardIds.at(i-1);
    }

    auto isDisplayed = [this](const int& id){
        for(int i = 1; i < m_displayBoardIds.size(); i++){
            if(m_displayBoardIds.at(i) == id){
                return true;
            }
        }
        return false;
    };

    {
        int frontId = m_displayBoardIds.front();
        frontId = (frontId+1)%m_boards.size();
        
        while(frontId != m_displayBoardIds.front()){
            if(!isDisplayed(frontId)){
                m_displayBoardIds.front() = frontId;
                break;
            }

            frontId = (frontId+1)%m_boards.size();
        }
    }

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::gotoRightBoard(){

    if(m_maxBoardRows == 1){
        shiftBoardsRight();
        return;
    }

    activeBoard().deselect();

    if(m_displayBoardIds.size() < 2){
        int& id = m_displayBoardIds.at(0);
        id = (id + 1)%m_boards.size();
    }
    else if(m_activeBoardIndex < m_displayBoardIds.size()-1){
        m_activeBoardIndex++;
    }
    else if(m_displayBoardIds.back() == m_boards.size()-1){
        displayFirstBoards();
        m_activeBoardIndex = 0;
    }
    else{
        for(auto it = m_displayBoardIds.begin(); it != m_displayBoardIds.end();it++){
            int newId = *it + m_maxBoardColumns;
            if(newId >= m_boards.size()){
                m_displayBoardIds.erase(it, m_displayBoardIds.end());
                break;
            }
            *it = newId;
        }
        m_activeBoardIndex += 1 - m_maxBoardColumns;
    }

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::gotoLeftBoard(){

    if(m_maxBoardRows == 1){
        shiftBoardsLeft();
        return;
    }

    activeBoard().deselect();

    if(m_displayBoardIds.size() < 2){
        int& id = m_displayBoardIds.at(0);
        id = (m_boards.size() + id - 1)%m_boards.size();
    }
    else if(m_activeBoardIndex > 0){
        m_activeBoardIndex--;
    }
    else if(m_displayBoardIds.at(0) == 0){
        displayLastBoards();
        m_activeBoardIndex = m_displayBoardIds.size()-1;
    }
    else{
        for(auto& id : m_displayBoardIds){
            id -= m_maxBoardColumns;
        }
        for(int i = m_displayBoardIds.size(); i < m_maxBoardRows*m_maxBoardColumns; i++){
            int id = m_displayBoardIds.back()+1;
            m_displayBoardIds.push_back(id);
        }
        m_activeBoardIndex = m_maxBoardColumns-1;
    }

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::gotoUpBoard(){

    if(m_maxBoardRows < 2){
        return;
    }

    if(m_displayBoardIds.size() <= m_maxBoardColumns){
        return;
    }

    activeBoard().deselect();

    if(m_activeBoardIndex > m_maxBoardColumns-1){
        m_activeBoardIndex -= m_maxBoardColumns;
    }
    else if(m_displayBoardIds.at(m_activeBoardIndex) < m_maxBoardColumns){
        displayLastBoards();
        
        int oldX = m_activeBoardIndex % m_maxBoardColumns;
        int lastX = (m_boards.size() - 1) % m_maxBoardColumns;

        m_activeBoardIndex = m_displayBoardIds.size() - 1;
        if(oldX < lastX){
            m_activeBoardIndex += oldX - lastX;
        }
    }
    else{
        for(auto& id : m_displayBoardIds){
            id -= m_maxBoardColumns;
        }
        for(int i = m_displayBoardIds.size(); i < m_maxBoardRows*m_maxBoardColumns; i++){
            int id = m_displayBoardIds.back()+1;
            m_displayBoardIds.push_back(id);
        }
    }

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::gotoDownBoard(){

    if(m_maxBoardRows < 2){
        return;
    }

    if(m_displayBoardIds.size() <= m_maxBoardColumns){
        return;
    }

    activeBoard().deselect();

    if(m_activeBoardIndex/m_maxBoardColumns < (m_displayBoardIds.size()-1)/m_maxBoardColumns){
        int newId = m_activeBoardIndex + m_maxBoardColumns;
        if(newId > m_displayBoardIds.size() - 1){
            newId = m_displayBoardIds.size() - 1;
        }
        m_activeBoardIndex = newId;
    }
    else if(m_displayBoardIds.at(m_activeBoardIndex)/m_maxBoardColumns >= (m_boards.size()-1)/m_maxBoardColumns){
        displayFirstBoards();
        m_activeBoardIndex = m_activeBoardIndex % m_maxBoardColumns;
    }
    else{
        for(auto it = m_displayBoardIds.begin(); it != m_displayBoardIds.end(); it++){
            int newId = *it + m_maxBoardColumns;
            if(newId >= m_boards.size()){
                m_displayBoardIds.erase(it, m_displayBoardIds.end());
                m_activeBoardIndex = m_displayBoardIds.size() - 1;
                break;
            }
            *it = newId;
        }
    }

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getSize());
    }
}

void WorkWindow::saveBoard(){
    activeBoard().save();
}

void WorkWindow::savePdf(){
    m_pdfHandler.savePdf(m_boards);
}

void WorkWindow::flipBoard(){
    activeBoard().flipBoard();
}

void WorkWindow::addLeftInsideLabels(){
    activeBoard().addLeftInsideLabels();
}

void WorkWindow::addBottomInsideLabels(){
    activeBoard().addBottomInsideLabels();
}

void WorkWindow::addLeftOutsideLabels(){
    activeBoard().addLeftOutsideLabels();
}

void WorkWindow::addRightOutsideLabels(){
    activeBoard().addRightOutsideLabels();
}

void WorkWindow::addTopOutsideLabels(){
    activeBoard().addTopOutsideLabels();
}

void WorkWindow::addBottomOutsideLabels(){
    activeBoard().addBottomOutsideLabels();
}

void WorkWindow::removeLeftInsideLabels(){
    activeBoard().removeLeftInsideLabels();
}

void WorkWindow::removeBottomInsideLabels(){
    activeBoard().removeBottomInsideLabels();
}

void WorkWindow::removeLeftOutsideLabels(){
    activeBoard().removeLeftOutsideLabels();
}

void WorkWindow::removeRightOutsideLabels(){
    activeBoard().removeRightOutsideLabels();
}

void WorkWindow::removeTopOutsideLabels(){
    activeBoard().removeTopOutsideLabels();
}

void WorkWindow::removeBottomOutsideLabels(){
    activeBoard().removeBottomOutsideLabels();
}

void WorkWindow::setCoordinateSize(const float& size){
    activeBoard().setCoordinateSize(size);    
}

void WorkWindow::addTileColumnRight(){
    activeBoard().addTileColumnRight();
}

void WorkWindow::addTileColumnLeft(){
    activeBoard().addTileColumnLeft();
}

void WorkWindow::removeTileColumnRight(){
    activeBoard().removeTileColumnRight();
}

void WorkWindow::removeTileColumnLeft(){
    activeBoard().removeTileColumnLeft();
}

void WorkWindow::addTileRowUp(){
    activeBoard().addTileRowUp();
}

void WorkWindow::addTileRowDown(){
    activeBoard().addTileRowDown();
}

void WorkWindow::removeTileRowUp(){
    activeBoard().removeTileRowUp();
}

void WorkWindow::removeTileRowDown(){
    activeBoard().removeTileRowDown();
}

void WorkWindow::addBoardBorder(){
    activeBoard().addBorder();
}

void WorkWindow::removeBoardBorder(){
    activeBoard().removeBorder();
}

void WorkWindow::addTurnToken(){
    activeBoard().addTurnToken();
}

void WorkWindow::removeTurnToken(){
    activeBoard().removeTurnToken();
}

void WorkWindow::useAddEntityTool(const Coord& coord, const LogicEntity& newEntity){

    auto occupying_entity_o = activeBoard().getLogicEntity(coord);

    if(occupying_entity_o == std::nullopt){
        activeBoard().addEntity(coord, newEntity);
        return;
    }

    if(occupying_entity_o.value() == newEntity){
        activeBoard().removeEntity(coord);
        return;
    }

    activeBoard().removeEntity(coord);
    activeBoard().addEntity(coord, newEntity);
}

void WorkWindow::useAddEntityAtSelectionTool(const LogicEntity& newEntity){
    activeBoard().addEntityAtSelection(newEntity);
}

void WorkWindow::updateTexture(){

    if(!m_texture.isInitialized()){
        return;
    }

    m_texture.clear();

    for(int id : m_displayBoardIds){
        if(id < m_boards.size()){
            m_texture.draw(m_boards.at(id));
        }
    }
    m_texture.draw(m_boardSelectHighlight);

    m_texture.display();
}

sigrid::Board& WorkWindow::activeBoard(){
    return m_boards.at(activeId());
}

const sigrid::Board& WorkWindow::activeBoard() const{
    return m_boards.at(activeId());
}

int& WorkWindow::activeId() {
    return m_displayBoardIds.at(m_activeBoardIndex);
}

const int& WorkWindow::activeId() const{
    return m_displayBoardIds.at(m_activeBoardIndex);
}

std::string WorkWindow::getUniqueName(const std::string& name){
    std::string newName(name);
    while(true){
        
        bool exists = false;
        for(const auto& board: m_boards){
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

    auto tile_o = activeBoard().getTile(coord);

    if(tile_o == std::nullopt){
        std::cerr << "WorkWindow: unable to find logic tile "
            << coord.getNotation() << " on board with id "
            << activeId()
            << " when adding highlight" << std::endl;
        return;
    }

    auto occupyingColor_o = tile_o.value().getHighlightColorId();

    if(occupyingColor_o == std::nullopt){
        activeBoard().addTileHighlight(coord, colorId);
        return;
    }

    if(occupyingColor_o.value() == colorId){
        activeBoard().removeTileHighlight(coord);
        return;
    }

    activeBoard().removeTileHighlight(coord);
    activeBoard().addTileHighlight(coord, colorId);
}

void WorkWindow::useAddArrowTool(const Coord& fromCoord, const Coord& toCoord, const int& colorId){

    auto occupyingArrow_o = activeBoard().getLogicArrow({fromCoord, toCoord});

    if(occupyingArrow_o == std::nullopt){
        activeBoard().addArrow(fromCoord, toCoord, LogicArrow{colorId});
        return;
    }

    if(occupyingArrow_o.value().getColorId() == colorId){
        activeBoard().removeArrow(fromCoord, toCoord);
        return;
    }

    activeBoard().removeArrow(fromCoord, toCoord);
    activeBoard().addArrow(fromCoord, toCoord, LogicArrow{colorId});
}

void WorkWindow::updateBoardLayout(){

    unsigned int i = 0;
    for(unsigned int y = 0; y < m_maxBoardRows; y++){
        for(unsigned int x = 0; x < m_maxBoardColumns; x++){
            m_layout.setFromXCoord(LayoutItem{i}, 1 + 2*x);
            m_layout.setToXCoord(LayoutItem{i}, 2 + 2*x);
            m_layout.setFromYCoord(LayoutItem{i}, 1 + 2*y);
            m_layout.setToYCoord(LayoutItem{i}, 2 + 2*y);
            i++;
        }
    }
}

void WorkWindow::updateSelectionHighlight(){

    if(m_displayBoardIds.size() < 2){
        m_boardSelectHighlight.hide();
        return;
    }

    const auto& board = activeBoard();
    const float& thickness = m_boardSelectHighlight.getThickness();
    sf::Vector2f position = board.getTopLeftPosition();
    position -= sf::Vector2f{thickness, thickness};
    m_boardSelectHighlight.setTopLeftPosition(position);
    m_boardSelectHighlight.setEnclosedArea(board.getDisplaySize());
    m_boardSelectHighlight.show();
}

void WorkWindow::displayFirstBoards(){

    m_displayBoardIds.clear();
    for(int id = 0; id < m_maxBoardColumns * m_maxBoardRows; id++){
        if(id >= m_boards.size()){
            break;
        }
        m_displayBoardIds.push_back(id);
    }
}

void WorkWindow::displayLastBoards(){

    m_displayBoardIds.clear();

    if(m_maxBoardRows == 1){
        int lastId = m_boards.size()-1;
        int firstDisplayId = lastId - m_maxBoardColumns + 1;
        if(firstDisplayId < 0){
            firstDisplayId = 0;
        }
        for(int id = firstDisplayId; id < m_boards.size(); id++){
            m_displayBoardIds.push_back(id);
        }
        return;
    }
    
    int numColumns = m_maxBoardColumns;
    if(numColumns > m_boards.size()){
        numColumns = m_boards.size();
    }
    int lastId = m_boards.size()-1;
    int lastX = (m_boards.size()-1)%numColumns;
    int maxDisplayBoards = numColumns*m_maxBoardRows;
    if(maxDisplayBoards > m_boards.size()){
        maxDisplayBoards = m_boards.size();
    }
    int offsetX = numColumns - 1 - lastX;
    if(maxDisplayBoards == m_boards.size()){
        offsetX = 0;
    }
    int numDisplayBoards = maxDisplayBoards - offsetX;

    int topLeftId = lastId - numDisplayBoards + 1;

    if(topLeftId < 0){
        topLeftId = 0;
    }
    for(int id = topLeftId; id < m_boards.size(); id++){
        m_displayBoardIds.push_back(id);
    }
}

void WorkWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_texture.isInitialized()){
        return;
    }

    target.draw(m_texture);
}