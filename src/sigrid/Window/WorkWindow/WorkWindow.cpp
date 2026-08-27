#include "sigrid/Window/WorkWindow/WorkWindow.h"

#include <iostream>

#include <SFML/Graphics/RenderTexture.hpp>

#include "sigrid/utilities/FileSystem/FileSystem.h"
#include "sigrid/Tool/Tool.h"
#include "sigrid/Entity/Tile/GraphicTiles.h"
#include "sigrid/Entity/GraphicEntities.h"
#include "sigrid/Entity/Shape/Arrow/GraphicArrows.h"
#include "sigrid/Board/BoardLabels.h"
#include "sigrid/Entity/TurnToken/TurnToken.h"

bool sigrid::WorkWindow::loadBoards(const sigrid_list::Vector<BoardContainer> boardContainers){

    int id = 0;
    for(const auto& boardContainer: boardContainers){

        BoardStateContainer boardStateData;

        if(sigrid_filesystem::exists(boardContainer.stateFilename)){
        
            if(boardStateData.load(boardContainer.stateFilename)){
                std:: cout << "Board data: " << boardContainer.stateFilename << " loaded" << std::endl;
            }
            else if (boardStateData.load(m_resetBoardFilename)){
                std::cerr << "WorkWindow: Failed to read Board data: " << boardContainer.stateFilename << std::endl;
                std::cerr << "Board data: " << m_resetBoardFilename << " loaded instead" << std::endl;
            }
            else{
                std::cerr << "WorkWindow: Failed to read both " << boardContainer.stateFilename
                << " and " << m_resetBoardFilename << "." << std::endl;
                std::cerr << "WorkWindow: Failed to load board." << std::endl;
                return false;
            }
        }
        else if (boardStateData.load(m_resetBoardFilename)){
            std::cout << "Board data: " << m_resetBoardFilename << " loaded" << std::endl;
        }
        else{
            std::cerr << "WorkWindow: Failed to read " << m_resetBoardFilename << std::endl;
            std::cerr << "WorkWindow: Failed to load board." << std::endl;
            return false;
        }

        loadBoard(id, boardContainer);
        loadBoardState(id, boardStateData);
        std::cout << "Save location: " << getSaveFilename() << std::endl;

        ++id;
    }
    return true;
}

void sigrid::WorkWindow::loadBoard(const int& id, const BoardContainer& container){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    while(m_boards.size() <= id){
        auto newBoard_o = m_boards.at(0);
        if(newBoard_o == std::nullopt){
            std::cerr << "WorkWindow: Failed to get defaultBoard."
                << " loadBoardState failed" << std::endl;
            return;
        }
        m_boards.push_back(std::move(newBoard_o.value()));
    }

    auto board_o = m_boards.at(id);
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.setFilename(container.stateFilename);
    board.setImageFilename(container.imageFilename);
}

void sigrid::WorkWindow::setResetBoardFilename(const sigrid::String& filename){
    m_resetBoardFilename = filename;
}

const sigrid::String& sigrid::WorkWindow::getResetBoardFilename() const{
    return m_resetBoardFilename;
}

void sigrid::WorkWindow::setDefaultBoardImageFilename(const sigrid::String& filename){
    m_defaultBoardImageFilename = filename;
}

const sigrid::String& sigrid::WorkWindow::getDefaultBoardImageFilename() const{
    return m_defaultBoardImageFilename;
}

void sigrid::WorkWindow::setTileColorManagerPtr(ColorManager* const managerPtr){
    
    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards){
        board.setTileColorManagerPtr(managerPtr);
    }
}

void sigrid::WorkWindow::setPieceManagerPtr(PieceManager* const managerPtr){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards){
        board.setPieceManagerPtr(managerPtr);
    }
}

void sigrid::WorkWindow::setArrowColorManagerPtr(ColorManager* const managerPtr){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards){
        board.setArrowColorManagerPtr(managerPtr);
    }
}

void sigrid::WorkWindow::setFontManagerPtr(FontManager* const managerPtr){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards){
        board.setFontManagerPtr(managerPtr);
    }
}

bool sigrid::WorkWindow::load(const WorkWindowContainer& container){

    if(!m_boards.setSize(container.boardColumns, container.boardRows)){
        return false;
    }

    updateBoardLayout();

    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
    return true;
}

sigrid::WorkWindowContainer sigrid::WorkWindow::getContainer() const{

    WorkWindowContainer container;
    container.boardColumns = m_boards.currentDisplayColumns();
    container.boardRows = m_boards.currentDisplayRows();

    return container;
}

void sigrid::WorkWindow::loadGraphicData(const BoardDesignContainer& graphicData){

    m_boardSelectHighlight.hide();
    m_boardSelectHighlight.setThickness(10);
    sigrid::Color selectColor;
    selectColor.setRGB(0x6464ff);
    m_boardSelectHighlight.setColor(selectColor);

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    for(auto& board: m_boards){
        board.loadGraphicData(graphicData);
    }
}

std::optional<sigrid::BoardDesignContainer> sigrid::WorkWindow::getBoardStyleContainer() const{

    const auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return std::nullopt;
    }
    auto& board = board_o.value().get();

    return board.getStyleContainer();
}

void sigrid::WorkWindow::loadBoardState(const int& id, const BoardStateContainer& boardStateData){

    if(m_boards.size() == 0){
        Board board;
        m_boards.push_back(std::move(board));
    }

    while(m_boards.size() <= id){
        auto newBoard_o = m_boards.at(0);
        if(newBoard_o == std::nullopt){
            std::cerr << "WorkWindow: Failed to get defaultBoard."
                << " Filed to load BoardState" << std::endl;
            return;
        }
        m_boards.push_back(std::move(newBoard_o.value()));
    }

    auto board_o = m_boards.at(id);
    if(board_o == std::nullopt){
        std::cerr << "WorkWindow: Failed to load board with id " << id << "."
            << " Failed to load BoardState" << std::endl;
        return;
    }
    auto& board = board_o.value().get();

    board.loadBoardState(boardStateData);

    if(!board.isImageFilenameSet()){
        board.setImageFilename(m_defaultBoardImageFilename);
    }

    updateBoardLayout();
    m_pdfHandler.updateLayout();
}

sigrid_list::Vector<sigrid::BoardContainer> sigrid::WorkWindow::getBoardContainers() const{

    sigrid_list::Vector<sigrid::BoardContainer> boardContainers;
    for(auto& board: m_boards){
        boardContainers.push_back(board.getContainer());
    }
    return boardContainers;
}

void sigrid::WorkWindow::createGraphic(const sigrid::Size_f& size){

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
        sigrid::Position_f boardTopLeftPosition = boardTopLeftPosition_o.value();

        auto board_o = m_boards.atDisplay(i);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();
        int boardWidth = board.getImageWidth();
        int boardHeight = board.getImageHeight();
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

void sigrid::WorkWindow::loadFen(const sigrid::String& fen){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.loadFen(fen);
}

sigrid::String sigrid::WorkWindow::getName() const{

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

sigrid::String sigrid::WorkWindow::getSaveFilename() const{

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return "";
    }
    auto& board = board_o.value().get();

    return board.getFilename();
}

sigrid::String sigrid::WorkWindow::getFen() const{

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return "";
    }
    auto& board = board_o.value().get();

    return board.getFen();
}

void sigrid::WorkWindow::setPosition(const sigrid::Position_f& position){
    m_texture.setPosition(position);
}

int sigrid::WorkWindow::getNumColumns() const{

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

bool sigrid::WorkWindow::contains(const sigrid::Position_f& point) const{
    return m_texture.contains(point);
}

bool sigrid::WorkWindow::isCoordinatesOutside() const{

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return false;
    }
    auto& board = board_o.value().get();

    return board.isCoordinatesOutside();
}

void sigrid::WorkWindow::mousePress(const sigrid::Position_f& windowPosition){

    auto activeBoard_o = m_boards.atSelection();

    if(activeBoard_o){
        activeBoard_o.value().get().removeDragArrow();
    }

    sigrid::Position_f position = windowPosition - m_texture.getPosition();

    for(int displayIndex = 0; displayIndex < m_boards.currentDisplaySize(); displayIndex++){
        
        auto board_o = m_boards.atDisplay(displayIndex);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();
        
        if(!board.contains(position)){
            continue;
        }
        if(m_boards.isDisplayedElementSelected(displayIndex)){
            if(activeBoard_o){
                activeBoard_o.value().get().deselect();
            }
            m_boards.select(displayIndex);
            updateSelectionHighlight();
        }
        return;
    }
}

std::optional<sigrid_action::Action> sigrid::WorkWindow::clicked(const sigrid::Tool& tool, const sigrid::Position_f& pressPosition, const sigrid::Position_f& releasePosition){
    
    auto activeBoard_o = m_boards.atSelection();

    if(activeBoard_o){
        activeBoard_o.value().get().removeDragArrow();
    }

    sigrid::Position_f from = pressPosition - m_texture.getPosition();
    sigrid::Position_f to = releasePosition - m_texture.getPosition();

    for(int displayIndex = 0; displayIndex < m_boards.currentDisplaySize(); displayIndex++){
        
        auto board_o = m_boards.atDisplay(displayIndex);
        if(board_o == std::nullopt){
            continue;
        }
        auto& board = board_o.value().get();
        
        if(board.isWithinTurnToken(from) &&
        board.isWithinTurnToken(to)){
            board.toggleTurnToken();
            return std::nullopt;
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
            return std::nullopt;
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
                return std::nullopt;
            case ToolSelection::EntityAdder:
            {
                auto tool_o = tool.getEntity();
                if(tool_o == std::nullopt){
                    return std::nullopt;
                }
                auto tool = tool_o.value();
                useAddEntityTool(toCoord, tool);
                return std::nullopt;
            }
            case ToolSelection::EntityPicker:
            {
                auto logicEntity_o = board.getLogicEntity(toCoord);
                if(logicEntity_o == std::nullopt){
                    return std::nullopt;
                }
                sigrid_action::PickEntity action{logicEntity_o.value()};
                return action;
            }
            case ToolSelection::DrawArrow:
                if(fromCoord == toCoord){
                    useAddTileHighlightTool(toCoord, tool.getArrowColorId());
                    return std::nullopt;
                }
                useAddArrowTool(fromCoord, toCoord, tool.getArrowColorId());
                return std::nullopt;
            default:
                return std::nullopt;
        }
    }
    return std::nullopt;
}

void sigrid::WorkWindow::dragMouse(const Tool& tool, const sigrid::Position_f& pressPosition, const sigrid::Position_f& currentPosition){
    
    sigrid::Position_f from = pressPosition - m_texture.getPosition();
    sigrid::Position_f to = currentPosition - m_texture.getPosition();

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

void sigrid::WorkWindow::reset(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    BoardStateContainer boardStateData;
    boardStateData.load(m_resetBoardFilename);
    board.loadBoardState(boardStateData);
}

void sigrid::WorkWindow::clear(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.clearEntities();
    board.clearArrows();
}

void sigrid::WorkWindow::print(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.print();
}

void sigrid::WorkWindow::newBoard(){

    auto activeBoard_o = m_boards.atSelection();

    if(activeBoard_o){
        activeBoard_o.value().get().deselect();
    }
    Board newBoard;
    if(activeBoard_o){
        newBoard = activeBoard_o.value().get();
    }

    sigrid::String newName = getUniqueName(newBoard.getFilename());
    sigrid::String newImageName = getUniqueName(newBoard.getImageFilename());

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

void sigrid::WorkWindow::addBoard(const sigrid::String& boardFilename){

    auto activeBoard_o = m_boards.atSelection();

    if(activeBoard_o){
        activeBoard_o.value().get().deselect();
    }
    Board newBoard;
    if(activeBoard_o){
        newBoard = activeBoard_o.value().get();
    }

    sigrid::String newImageName = getUniqueName(newBoard.getImageFilename());

    std::cout << "New board name " << boardFilename << std::endl;
    std::cout << "New image name " << newImageName << std::endl;    
    
    newBoard.setFilename(boardFilename);
    newBoard.setImageFilename(newImageName);

    sigrid::BoardStateContainer boardContainer;
    boardContainer.load(boardFilename);

    newBoard.loadBoardState(boardContainer);

    m_boards.push_back(std::move(newBoard));
    m_boards.selectLast();

    if(m_texture.isInitialized()){
        createGraphic(m_texture.getTextureSize());
    }
}

void sigrid::WorkWindow::addBoardColumn(){

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

void sigrid::WorkWindow::removeBoardColumn(){

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

void sigrid::WorkWindow::addBoardRow(){

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

void sigrid::WorkWindow::removeBoardRow(){

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

void sigrid::WorkWindow::shiftBoardsLeft(){

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

void sigrid::WorkWindow::shiftBoardsRight(){

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

void sigrid::WorkWindow::gotoRightBoard(){

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

void sigrid::WorkWindow::gotoLeftBoard(){

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

void sigrid::WorkWindow::gotoUpBoard(){

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

void sigrid::WorkWindow::gotoDownBoard(){

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

void sigrid::WorkWindow::saveBoards(){

    for(auto& board: m_boards){
        board.save();
    }
}

void sigrid::WorkWindow::saveBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.save();
}

void sigrid::WorkWindow::savePdf(){
    m_pdfHandler.savePdf(m_boards);
}

void sigrid::WorkWindow::flipBoard(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.flipBoard();
}

void sigrid::WorkWindow::addLeftInsideLabels(){

    for(auto& board: m_boards){
        board.addLeftInsideLabels();
    }
}

void sigrid::WorkWindow::addBottomInsideLabels(){

    for(auto& board: m_boards){
        board.addBottomInsideLabels();
    }
}

void sigrid::WorkWindow::addLeftOutsideLabels(){

    for(auto& board: m_boards){
        board.addLeftOutsideLabels();
    }
}

void sigrid::WorkWindow::addRightOutsideLabels(){

    for(auto& board: m_boards){
        board.addRightOutsideLabels();
    }
}

void sigrid::WorkWindow::addTopOutsideLabels(){

    for(auto& board: m_boards){
        board.addTopOutsideLabels();
    }
}

void sigrid::WorkWindow::addBottomOutsideLabels(){

    for(auto& board: m_boards){
        board.addBottomOutsideLabels();
    }
}

void sigrid::WorkWindow::removeLeftInsideLabels(){

    for(auto& board: m_boards){
        board.removeLeftInsideLabels();
    }
}

void sigrid::WorkWindow::removeBottomInsideLabels(){

    for(auto& board: m_boards){
        board.removeBottomInsideLabels();
    }
}

void sigrid::WorkWindow::removeLeftOutsideLabels(){

    for(auto& board: m_boards){
        board.removeLeftOutsideLabels();
    }
}

void sigrid::WorkWindow::removeRightOutsideLabels(){

    for(auto& board: m_boards){
        board.removeRightOutsideLabels();
    }
}

void sigrid::WorkWindow::removeTopOutsideLabels(){

    for(auto& board: m_boards){
        board.removeTopOutsideLabels();
    }
}

void sigrid::WorkWindow::removeBottomOutsideLabels(){

    for(auto& board: m_boards){
        board.removeBottomOutsideLabels();
    }
}

void sigrid::WorkWindow::setCoordinateSize(const float& size){

    for(auto& board: m_boards){
        board.setCoordinateSize(size);    
    }
}

void sigrid::WorkWindow::addTileColumnRight(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileColumnRight();
}

void sigrid::WorkWindow::addTileColumnLeft(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileColumnLeft();
}

void sigrid::WorkWindow::removeRightTileColumn(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeRightTileColumn();
}

void sigrid::WorkWindow::removeLeftTileColumn(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeLeftTileColumn();
}

void sigrid::WorkWindow::addTileRowUp(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileRowUp();
}

void sigrid::WorkWindow::addTileRowDown(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addTileRowDown();
}

void sigrid::WorkWindow::removeTopTileRow(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeTopTileRow();
}

void sigrid::WorkWindow::removeBottomTileRow(){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.removeBottomTileRow();
}

void sigrid::WorkWindow::addBoardBorder(){

    for(auto& board: m_boards){
        board.addBorder();
    }
}

void sigrid::WorkWindow::removeBoardBorder(){

    for(auto& board: m_boards){
        board.removeBorder();
    }
}

void sigrid::WorkWindow::addTurnToken(){

    for(auto& board: m_boards){
        board.addTurnToken();
    }
}

void sigrid::WorkWindow::removeTurnToken(){

    for(auto& board: m_boards){
        board.removeTurnToken();
    }
}

void sigrid::WorkWindow::useAddEntityTool(const sigrid_coord::Coord& coord, const LogicEntity& newEntity){

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

void sigrid::WorkWindow::useAddEntityAtSelectionTool(const LogicEntity& newEntity){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    board.addEntityAtSelection(newEntity);
}

void sigrid::WorkWindow::updateTexture(){

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

sigrid::String sigrid::WorkWindow::getUniqueName(const sigrid::String& name){
    
    sigrid::String newName(name);
    while(true){
        
        bool exists = false;
        for(const auto& board: m_boards){
            if(board.getFilename() == newName || board.getImageFilename() == newName){
                exists = true;
                break;
            }
        }
        if(!exists){
            if(!sigrid_filesystem::exists(newName)){
                break;
            }
        }

        auto endPos_o = newName.rfind('.');
        if(endPos_o == std::nullopt){
            std::cerr << "WorkWindow: No . in getUniqueName";
            return newName;
        }
        int endPos = endPos_o.value();

        auto startPos = endPos;

        auto startChar_o = newName.at(startPos-1);

        while(startChar_o != std::nullopt){
            char startChar = startChar_o.value();
            if(!std::isdigit(startChar)){
                break;
            }
            startPos--;
            startChar_o = newName.at(startPos-1);
        }
        if(startPos == endPos){
            newName.insert(startPos, "2");
        }
        else{
            auto digitString_o = newName.substr(startPos,endPos-startPos);
            if(digitString_o == std::nullopt){
                return "";
            }
            sigrid::String digitString = digitString_o.value();

            auto digit_o = digitString.toInt();
            if(digit_o == std::nullopt){
                return "";
            }
            int digit = digit_o.value();

            digit++;
            std::string stdDigitString = std::to_string(digit);
            digitString.set(std::move(stdDigitString));
            newName.erase(startPos,endPos-startPos);
            newName.insert(startPos, digitString);
        }
    }
    return newName;
}

void sigrid::WorkWindow::useAddTileHighlightTool(const sigrid_coord::Coord& coord, const int& colorId){

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

void sigrid::WorkWindow::useAddArrowTool(const sigrid_coord::Coord& fromCoord, const sigrid_coord::Coord& toCoord, const int& colorId){

    auto board_o = m_boards.atSelection();
    if(board_o == std::nullopt){
        return;
    }
    auto& board = board_o.value().get();

    auto occupyingArrow_o = board.getLogicArrow({fromCoord, toCoord});
    LogicArrow logicArrow;
    logicArrow.setColor(colorId);

    if(occupyingArrow_o == std::nullopt){
        board.addArrow(fromCoord, toCoord, logicArrow);
        return;
    }

    if(occupyingArrow_o.value().getColorId() == colorId){
        board.removeArrow(fromCoord, toCoord);
        return;
    }

    board.removeArrow(fromCoord, toCoord);
    board.addArrow(fromCoord, toCoord, logicArrow);
}

void sigrid::WorkWindow::updateBoardLayout(){

    unsigned int i = 0;
    for(int y = 0; y < m_boards.maxDisplayRows(); y++){
        for(int x = 0; x < m_boards.maxDisplayColumns(); x++){
            m_layout.setFromXCoord(LayoutItem{i}, 1 + 2*x);
            m_layout.setToXCoord(LayoutItem{i}, 2 + 2*x);
            m_layout.setFromYCoord(LayoutItem{i}, 1 + 2*y);
            m_layout.setToYCoord(LayoutItem{i}, 2 + 2*y);
            i++;
        }
    }
}

void sigrid::WorkWindow::updateSelectionHighlight(){

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
    sigrid::Position_f position = board.getTopLeftPosition();
    position.x -= thickness;
    position.y -= thickness;
    m_boardSelectHighlight.setTopLeftPosition(position);
    m_boardSelectHighlight.setEnclosedArea(board.getDisplaySize());
    m_boardSelectHighlight.show();
}

void sigrid::WorkWindow::draw(sf::RenderTarget& target, sf::RenderStates states) const{

    if(!m_texture.isInitialized()){
        return;
    }

    target.draw(m_texture);
}