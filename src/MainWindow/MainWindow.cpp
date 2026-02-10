#include "MainWindow.h"

#include <iostream>

#include "../Action/Action.h"
#include "../Tool/Tool.h"

using namespace sigrid;


MainWindow::MainWindow(sf::Vector2u size, std::string windowName)
: m_window{sf::VideoMode(size), windowName}
, m_backgroundColor{sf::Color(30,30,30)}
, m_size{size}
, m_scale{1.f,1.f}
, m_piecePickerToBoardGap{10.f}{
    m_window.setFramerateLimit(60);

    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Left, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Right, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Middle, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Extra1, false});
    m_isMouseButtonPressedMap.insert({sf::Mouse::Button::Extra2, false});

    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Left, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Right, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Middle, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Extra1, {0,0}});
    m_mouseButtonPressedPositionMap.insert({sf::Mouse::Button::Extra2, {0,0}});

    sigrid::Tool tool1{sigrid::ToolSelection::Select};
    m_tools.insert({sf::Mouse::Button::Left,std::move(tool1)});
    sigrid::Tool tool2{sigrid::ToolSelection::DrawArrow};
    m_tools.insert({sf::Mouse::Button::Right, std::move(tool2)});
    sigrid::Tool tool3{sigrid::ToolSelection::PiecePicker};
    m_tools.insert({sf::Mouse::Button::Middle, std::move(tool3)});
    sigrid::Tool tool4{sigrid::ToolSelection::Select};
    m_tools.insert({sf::Mouse::Button::Extra1, std::move(tool4)});
    sigrid::Tool tool5{sigrid::ToolSelection::Select};
    m_tools.insert({sf::Mouse::Button::Extra2, std::move(tool5)});
    
}

void MainWindow::add(std::unique_ptr<sigrid::Menu> menu){
    m_menu = std::move(menu);
}

void MainWindow::add(std::unique_ptr<sigrid::WorkWindow> workWindow){
    m_workWindow = std::move(workWindow);
}

void MainWindow::add(std::unique_ptr<sigrid::ToolWindow> toolWindow){
    m_toolWindow = std::move(toolWindow);
}

void MainWindow::add(std::unique_ptr<sigrid::ToolPickerWindow> toolPickerWindow){
    m_toolPickerWindow = std::move(toolPickerWindow);
}

void MainWindow::run(){
    
    createGraphic();

    while (m_window.isOpen())
    {
        handleEvents();
        redraw();
    }
}

void MainWindow::createGraphic(){

    struct WindowCoordId{
        unsigned int fromX;
        unsigned int toX;
        unsigned int fromY;
        unsigned int toY;
    };

    WindowCoordId menuCoordId;
    WindowCoordId toolPickerCoordId;
    WindowCoordId toolWindowCoordId;
    WindowCoordId workWindowCoordId;

    {
        //Top row x id coordinates

        menuCoordId.fromX = 0;
        if(m_menu && m_menu->isCollapsed()){
            menuCoordId.toX = 1;
        }
        else{
            menuCoordId.toX = 3;
        }
    }

    {
        //second row x id coordinates

        toolPickerCoordId.fromX = 0;
        toolPickerCoordId.toX = 1;

        if(m_toolPickerWindow && !m_toolPickerWindow->isHidden() ||
        m_toolWindow && !m_toolWindow->isHidden() ||
        m_menu && !m_menu->isPinned()){

            workWindowCoordId.fromX = 2;
        }
        else{
            workWindowCoordId.fromX = 0;
        }
        workWindowCoordId.toX = 3;
    }

    {
        //Third row x id coordinates
        toolWindowCoordId.fromX = 0;
        toolWindowCoordId.toX = 1;
    }

    {
        //Left column y id coordinates
        unsigned int y = 0;
        menuCoordId.fromY = 0;
        menuCoordId.toY = 1;
        if(m_menu){
            y = 1;
        }
        toolPickerCoordId.fromY = y;
        if(m_toolWindow){
            toolPickerCoordId.toY = 2;
        }
        else{
            toolPickerCoordId.toY = 3;
        }
        toolWindowCoordId.fromY = 2;
        toolWindowCoordId.toY = 3;
    }

    {
        //second column y id coordinates

        if(!m_menu || m_menu->isCollapsed()){
            workWindowCoordId.fromY = 0;
        }
        else{
            workWindowCoordId.fromY = 1;
        }

        workWindowCoordId.toY = 3;
    }

    float x[4];
    float y[4];

    x[0] = 0.f;
    x[3] = m_size.x;
    y[0] = 0.f;
    y[3] = m_size.y;

    float menuHeightCandidate1 = 40;
    float menuHeightCandidate2 = (float)m_size.y/10.f;
    float menuHeight;
    if(menuHeightCandidate1 < menuHeightCandidate2){
        menuHeight = menuHeightCandidate1;
    }
    else{
        menuHeight = menuHeightCandidate2;
    }
    y[1] = menuHeight;

    float toolHeightCandidate1 = 150;
    float toolHeightCandidate2 = (float)m_size.y/10.f;
    float toolHeight;
    if(toolHeightCandidate1 < toolHeightCandidate2){
        toolHeight = toolHeightCandidate1;
    }
    else{
        toolHeight = toolHeightCandidate2;
    }
    y[2] = m_size.y - toolHeight;    

    if(!m_toolPickerWindow || m_toolPickerWindow->isHidden()){
        x[1] = 120.f;
    }
    else{
        unsigned int toolPickerColumns = m_toolPickerWindow->getNumColumns();
        unsigned int toolPickerRows = m_toolPickerWindow->getNumRows();
        unsigned int boardColumns = m_workWindow->getNumColumns();

        float xCandidate1 = (x[3] - x[0])*((float)toolPickerColumns/(float)(toolPickerColumns+boardColumns));

        float toolPickerHeight = y[2]-y[1];
        unsigned int toolPickerSquareHeight = toolPickerHeight/toolPickerRows;
        unsigned int toolPickerSquareWidth = toolPickerSquareHeight;

        float xCandidate2 = toolPickerSquareWidth*toolPickerColumns;

        if(xCandidate2 < xCandidate1){
            x[1] = xCandidate2;
        }
        else{
            x[1] = xCandidate1;
        }

        if(x[1] < 120.f){
            x[1] = 120.f;
        }
    }
    x[2] = x[1]+m_piecePickerToBoardGap;

    if(m_menu){
        unsigned int menuWidth = (unsigned int)(x[menuCoordId.toX]-x[menuCoordId.fromX]);
        assert(menuWidth > 0);
        unsigned int menuHeight = (unsigned int)(y[menuCoordId.toY]-y[menuCoordId.fromY]);
        assert(menuHeight > 0);

        float menuXPos = x[menuCoordId.fromX];
        float menuYPos = y[menuCoordId.fromY];

        m_menu->createGraphic({menuWidth, menuHeight});
        m_menu->setPosition({menuXPos,menuYPos});
    }

    if(m_toolWindow){
        unsigned int toolWidth = (unsigned int)(x[toolWindowCoordId.toX]-x[toolWindowCoordId.fromX]);
        assert(toolWidth > 0);
        unsigned int toolHeight = (unsigned int)(y[toolWindowCoordId.toY]-y[toolWindowCoordId.fromY]);
        assert(toolHeight > 0);

        float toolXPos = x[toolWindowCoordId.fromX];
        float toolYPos = y[toolWindowCoordId.fromY];

        m_toolWindow->createGraphic({toolWidth, toolHeight});
        m_toolWindow->setPosition({toolXPos, toolYPos});
    }

    if(m_toolPickerWindow && !(m_toolPickerWindow->isHidden())){

        unsigned int toolPickerWidth = (unsigned int)(x[toolPickerCoordId.toX]-x[toolPickerCoordId.fromX]);
        assert(toolPickerWidth > 0);
        unsigned int toolPickerHeight = (unsigned int)(y[toolPickerCoordId.toY]-y[toolPickerCoordId.fromY]);
        assert(toolPickerHeight > 0);

        float toolPickerXPos = x[toolPickerCoordId.fromX];
        float toolPickerYPos = y[toolPickerCoordId.fromY];

        m_toolPickerWindow->createGraphic({toolPickerWidth, toolPickerHeight});
        m_toolPickerWindow->setPosition({toolPickerXPos, toolPickerYPos});
    }

    if(m_workWindow){

        unsigned int workWidth = (unsigned int)(x[workWindowCoordId.toX]-x[workWindowCoordId.fromX]);
        assert(workWidth > 0);
        unsigned int workHeight = (unsigned int)(y[workWindowCoordId.toY]-y[workWindowCoordId.fromY]);
        assert(workHeight > 0);

        float workXPos = x[workWindowCoordId.fromX];
        float workYPos = y[workWindowCoordId.fromY];

        m_workWindow->createGraphic({workWidth, workHeight});
        m_workWindow->setPosition({workXPos, workYPos});
    }
}

void MainWindow::resize(const sf::Vector2u& size){

    sf::FloatRect visibleArea{{0,0},{(float)size.x, (float)size.y}};

    m_window.setView((sf::View)(visibleArea));
    m_size = size;
    createGraphic();
}

void MainWindow::mouseButtonPress(const sf::Vector2i& position, const sf::Mouse::Button& button){

    sf::Vector2i scaledPosition{(int)(m_scale.x*position.x), (int)(m_scale.y*position.y)};

    m_mouseButtonPressedPositionMap.at(button) = scaledPosition;
    m_isMouseButtonPressedMap.at(button) = true;

}

void MainWindow::mouseButtonRelease(const sf::Vector2i& position, const sf::Mouse::Button& button){

    sf::Vector2i scaledPosition{(int)(m_scale.x*position.x), (int)(m_scale.y*position.y)};

    if(m_menu && m_menu->contains(scaledPosition)){
        sigrid::Tool *usedToolPtr = &m_tools.at(button);
        Action action = m_menu->clicked(*usedToolPtr, scaledPosition);
        handleAction(action);
    }
    else if(m_workWindow && m_workWindow->contains(scaledPosition)){
        sigrid::Tool* usedToolPtr = &m_tools.at(button);
        Action action = m_workWindow->clicked(*usedToolPtr, m_mouseButtonPressedPositionMap.at(button), scaledPosition);
        handleAction(action);
    }
    else if(m_toolWindow && m_toolWindow->contains(scaledPosition)){
        sigrid::Tool* usedToolPtr = &m_tools.at(button);
        Action action = m_toolWindow->clicked(*usedToolPtr, scaledPosition);
        handleAction(action);
    }
    else if(m_toolPickerWindow && m_toolPickerWindow->contains(scaledPosition)){
        sigrid::Tool* usedToolPtr = &m_tools.at(button);
        Action action = m_toolPickerWindow->clicked(*usedToolPtr, scaledPosition);
        handleAction(action);
    }
    m_isMouseButtonPressedMap.at(button) = false;
}

void MainWindow::keyPress(const sf::Keyboard::Key& keyboardKey){

    if(keyboardKey == sf::Keyboard::Key::Space){
        m_tools.at(sf::Mouse::Button::Left).setSelection(ToolSelection::Select);
        if(m_toolWindow){
            m_toolWindow->setSelectTool(sf::Mouse::Button::Left, ToolSelection::Select);
        }
    }
    else if(keyboardKey == sf::Keyboard::Key::Delete){
        //delete selected piece
    }
    return;
}

void MainWindow::textEnter(const char32_t& unicode){

    sf::String text{unicode};

    if(m_workWindow){
        m_workWindow->textEntered(text);
    }
}

void MainWindow::mouseMove(const sf::Vector2i& position){

    sf::Vector2i scaledPosition{(int)(m_scale.x*position.x), (int)(m_scale.y*position.y)};

    if(m_workWindow && m_workWindow->contains(scaledPosition)){
        sf::Mouse::Button buttons[5] = {sf::Mouse::Button::Left, sf::Mouse::Button::Right, sf::Mouse::Button::Middle, sf::Mouse::Button::Extra1, sf::Mouse::Button::Extra2};
        for(int i = 0; i < 5; i++){
            sigrid::Tool* usedToolPtr = &m_tools.at(buttons[i]);
            if(m_isMouseButtonPressedMap.at(buttons[i])){
                
                m_workWindow->dragMouse(*usedToolPtr, m_mouseButtonPressedPositionMap.at(buttons[i]), scaledPosition);
                
            }
        }
    }
}

void MainWindow::handleEvents(){
    while (const std::optional event = m_window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            m_window.close();
        }

        if(const auto* resized = event->getIf<sf::Event::Resized>()){
            resize(resized->size);
        }

        if(const auto* mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()){
            mouseButtonPress(mouseButtonPressed->position, mouseButtonPressed->button);
        }

        if(const auto* mouseButtonReleased = event->getIf<sf::Event::MouseButtonReleased>()){
            mouseButtonRelease(mouseButtonReleased->position, mouseButtonReleased->button);
        }

        if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
            keyPress(keyPressed->code);
        }

        if(const auto* textEntered = event->getIf<sf::Event::TextEntered>()){
            textEnter(textEntered->unicode);
        }

        if(const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>()){
            mouseMove(mouseMoved->position);
        }
    }
}

void MainWindow::handleAction(const sigrid::Action action){

    if(std::holds_alternative<ActionType::PinMenu>(action)){
        pinMenu();
        return;
    }
    else if(std::holds_alternative<ActionType::ShowMenu>(action)){
        showMenu();
        return;
    }
    else if(std::holds_alternative<ActionType::ToggleHeader>(action)){
        int headerId = std::get<ActionType::ToggleHeader>(action).headerId;
        toggleHeader(headerId);
    }
    else if(std::holds_alternative<ActionType::Reset>(action)){
        reset();
        return;
    }
    else if(std::holds_alternative<ActionType::Clear>(action)){
        clear();
        return;
    }
    else if(std::holds_alternative<ActionType::Print>(action)){
        print();
        return;
    }
    else if(std::holds_alternative<ActionType::PickPiece>(action)){
        
        sigrid::Piece piece = std::get<ActionType::PickPiece>(action).piece;
        pickPiece(piece);
        return;
    }
    else if(std::holds_alternative<ActionType::PickPieceColor>(action)){

        sigrid::Piece piece = std::get<ActionType::PickPieceColor>(action).piece;
        pickPieceColor(piece);
        return;
    }
    else if(std::holds_alternative<ActionType::PickArrow>(action)){

        int colorId = std::get<ActionType::PickArrow>(action).colorId;
        pickArrow(colorId);
        return;
    }
    else if(std::holds_alternative<ActionType::PickArrowColor>(action)){
        
        int colorId = std::get<ActionType::PickArrowColor>(action).colorId;
        pickArrowColor(colorId);
        return;
    }
    else if(std::holds_alternative<ActionType::SetTool>(action)){
        
        ActionType::SetTool a = std::get<ActionType::SetTool>(action);
        setTool(a.selection, a.button);
        return;
    }
    else if(std::holds_alternative<ActionType::ShowColorTools>(action)){
        showColorTools();
        return;
    }
    else if(std::holds_alternative<ActionType::HideColorTools>(action)){
        hideColorTools();
        return;
    }
    else if(std::holds_alternative<ActionType::ShowTools>(action)){
        showTools();
        return;
    }
    else if(std::holds_alternative<ActionType::HideTools>(action)){
        hideTools();
        return;
    }
    else if(std::holds_alternative<ActionType::SaveBoardImage>(action)){

        std::string imageFilename = std::get<ActionType::SaveBoardImage>(action).imageFileName;
        saveBoardImage(imageFilename);
        saveLogicBoard("saveData/diagrams/logic/board2.txt");
        return;
    }
    else if(std::holds_alternative<ActionType::AddCoordinates>(action)){
        addCoordinates();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveCoordinates>(action)){
        removeCoordinates();
        return;
    }
    else if(std::holds_alternative<ActionType::MoveCoordinatesOutside>(action)){
        moveCoordinatesOutside();
        return;
    }
    else if(std::holds_alternative<ActionType::MoveCoordinatesInside>(action)){
        moveCoordinatesInside();
        return;
    }
    else if(std::holds_alternative<ActionType::SetBigCoordinates>(action)){
        setBigCoordinates();
        return;
    }
    else if(std::holds_alternative<ActionType::SetSmallCoordinates>(action)){
        setSmallCoordinates();
        return;
    }
    else if(std::holds_alternative<ActionType::AddBoardBorder>(action)){
        addBoardBorder();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveBoardBorder>(action)){
        removeBoardBorder();
        return;
    }
    else if(std::holds_alternative<ActionType::AddPlayerToMoveToken>(action)){
        addPlayerToMoveToken();
        return;
    }
    else if(std::holds_alternative<ActionType::RemovePlayerToMoveToken>(action)){
        removePlayerToMoveToken();
        return;
    }
}

void MainWindow::pinMenu(){
    if(!m_menu){
        std::cout << "Unable to pin menu, Menu does not exist" << std::endl;
        return;
    }

    m_menu->pinMenu();
    m_menu->toggleItem("Pin Menu");
    createGraphic();
}

void MainWindow::showMenu(){
    if(!m_menu){
        std::cout << "Unable to show menu, Menu does not exist" << std::endl;
        return;
    }
    m_menu->showMenu();
    createGraphic();
}

void MainWindow::toggleHeader(const int headerId){
    if(!m_menu){
        std::cout << "Unable to toggle header, Menu does not exist" << std::endl;
        return;
    }
    m_menu->toggleHeader(headerId);
}

void MainWindow::reset(){
    if(!m_workWindow){
        std::cout << "Unable to reset board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->reset();
}

void MainWindow::clear(){
    if(!m_workWindow){
        std::cout << "Unable to clear board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->clear();
}

void MainWindow::print(){
    if(!m_workWindow){
        std::cout << "Unable to print board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->print();
}

void MainWindow::pickPiece(const sigrid::Piece& piece){
    if(!m_toolWindow){
        std::cout << "Unable to pick piece, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cout << "Unable to pick piece, toolpicker window does not exist" << std::endl;
        return;
    }
    m_tools.at(sf::Mouse::Button::Left).setPiece(piece);
    m_tools.at(sf::Mouse::Button::Left).setSelection(ToolSelection::PieceAdder);
    m_toolWindow->setSetPieceTool(piece);
    m_toolPickerWindow->setPieceColorTools(piece.logic().notation());
}

void MainWindow::pickPieceColor(const sigrid::Piece& piece){

    if(!m_toolWindow){
        std::cout << "Unable to pick piece color, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cout << "Unable to pick piece color, toolpicker window does not exist" << std::endl;
        return;
    }

    m_tools.at(sf::Mouse::Button::Left).setPiece(piece);
    m_tools.at(sf::Mouse::Button::Left).setSelection(ToolSelection::PieceAdder);
    m_toolWindow->setSetPieceTool(piece);
    m_toolPickerWindow->setPieceTools(piece.logic().colorId());
}

void MainWindow::pickArrow(const int colorId){
    if(!m_toolPickerWindow){
        std::cout << "Unable to pick arrow, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cout << "Unable to pick arrow color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_tools.at(sf::Mouse::Button::Left).setArrow(colorId);
    m_tools.at(sf::Mouse::Button::Left).setSelection(ToolSelection::DrawArrow);
    m_toolWindow->setAddArrowTool(colorId);
    m_toolPickerWindow->setArrowColors();
}

void MainWindow::pickArrowColor(const int colorId){
    if(!m_toolWindow){
        std::cout << "Unable to pick arrow color, toolWindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cout << "Unable to pick arrow color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_tools.at(sf::Mouse::Button::Left).setArrow(colorId);
    m_tools.at(sf::Mouse::Button::Left).setSelection(ToolSelection::DrawArrow);
    m_toolWindow->setAddArrowTool(colorId);
    m_toolPickerWindow->setAddArrowTool(colorId);
}

void MainWindow::setTool(const sigrid::ToolSelection& selection, const sf::Mouse::Button& button){
    if(!m_toolWindow){
        std::cout << "Unable to set tool, toolWindow does not exist" << std::endl;
        return;
    }
    m_tools.at(button).setSelection(selection);
    m_toolWindow->setSelectTool(button, selection);
}

void MainWindow::showColorTools(){

    if(!m_toolPickerWindow){
        std::cout << "Unable to show color tools, toolpicker window does not exist" << std::endl;
        return;
    }

    m_toolPickerWindow->showColorTools();
    if(m_menu){
        m_menu->toggleItem("Color Tools");
        
    }
    
    createGraphic();
}

void MainWindow::hideColorTools(){

    if(!m_toolPickerWindow){
        std::cout << "Unable to hide color tools, toolpicker window does not exist" << std::endl;
        return;
    }

    m_toolPickerWindow->hideColorTools();
    if(m_menu){
        m_menu->toggleItem("Color Tools");
    }

    createGraphic();
}

void MainWindow::showTools(){

    if(!m_toolPickerWindow){
        std::cout << "Unable to show tools, toolpicker window does not exist" << std::endl;
        return;
    }

    if(!m_toolWindow){
        std::cout << "Unable to show tools, tool window does not exist" << std::endl;
    }

    m_toolPickerWindow->show();
    m_toolWindow->show();
    if(m_menu){
        m_menu->toggleItem("Tool Window");
        m_menu->showItem("Color Tools");
    }
    
    createGraphic();
}

void MainWindow::hideTools(){
    if(!m_toolPickerWindow){
        std::cout << "Unable to toggle tools, toolpicker window does not exist" << std::endl;
        return;
    }

    if(!m_toolWindow){
        std::cout << "Unable to toggle tools, tool window does not exist" << std::endl;
    }

    m_toolPickerWindow->hide();
    m_toolWindow->hide();
    if(m_menu){
        m_menu->toggleItem("Tool Window");
        m_menu->hideItem("Color Tools");
    }
    
    createGraphic();
}

void MainWindow::saveLogicBoard(const std::string& filename){

    if(!m_workWindow){
        std::cout << "Unable to save board image, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->saveLogicBoard(filename);

}

void MainWindow::saveBoardImage(const std::string& imageFilename){

    if(!m_workWindow){
        std::cout << "Unable to save board image, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->saveBoardImage(imageFilename);
}

void MainWindow::addCoordinates(){
    if(!m_workWindow){
        std::cout << "Unable to show coordinates, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addCoordinates();

    if(m_menu){
        m_menu->toggleItem("Coordinates");
        m_menu->showItem("Move Coordinates");
        if(m_workWindow->isCoordinatesOutside()){
            m_menu->showItem("Set Coordinate Size");
        }
    }

    createGraphic();
}

void MainWindow::removeCoordinates(){
    if(!m_workWindow){
        std::cout << "Unable to hide coordinates, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeCoordinates();

    if(m_menu){
        m_menu->toggleItem("Coordinates");
        m_menu->hideItem("Move Coordinates");
        m_menu->hideItem("Set Coordinate Size");
    }

    createGraphic();
}

void MainWindow::moveCoordinatesOutside(){
    if(!m_workWindow){
        std::cout << "Unable to move coordinates, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->moveCoordinatesOutside();

    if(m_menu){
        m_menu->toggleItem("Move Coordinates");
        m_menu->showItem("Set Coordinate Size");
    }

    createGraphic();
}

void MainWindow::moveCoordinatesInside(){

    if(!m_workWindow){
        std::cout << "Unable to move coordinates, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->moveCoordinatesInside();

    if(m_menu){
        m_menu->toggleItem("Move Coordinates");
        m_menu->hideItem("Set Coordinate Size");
    }

    createGraphic();
}

void MainWindow::setBigCoordinates(){

    if(!m_workWindow){
        std::cout << "Unable to set big coordinates, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->setBigCoordinates();

    if(m_menu){
        m_menu->toggleItem("Set Coordinate Size");
    }

    createGraphic();
}

void MainWindow::setSmallCoordinates(){

    if(!m_workWindow){
        std::cout << "Unable to set big coordinates, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->setSmallCoordinates();

    if(m_menu){
        m_menu->toggleItem("Set Coordinate Size");
    }

    createGraphic();
}

void MainWindow::addBoardBorder(){

    if(!m_workWindow){
        std::cout << "Unable to add border to board, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addBoardBorder();

    if(m_menu){
        m_menu->toggleItem("Toggle Border");
    }

    createGraphic();
}

void MainWindow::removeBoardBorder(){

    if(!m_workWindow){
        std::cout << "Unable to remove border to board, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeBoardBorder();

    if(m_menu){
        m_menu->toggleItem("Toggle Border");
    }

    createGraphic();
}

void MainWindow::addPlayerToMoveToken(){

    if(!m_workWindow){
        std::cout << "Unable to add player-to-move token, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addPlayerToMoveToken();

    if(m_menu){
        m_menu->toggleItem("Toggle PlayerToMove Token");
    }

    createGraphic();
}

void MainWindow::removePlayerToMoveToken(){

    if(!m_workWindow){
        std::cout << "Unable to remove player-to-move token, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removePlayerToMoveToken();

    if(m_menu){
        m_menu->toggleItem("Toggle PlayerToMove Token");
    }

    createGraphic();
}

void MainWindow::redraw(){

    m_window.clear(m_backgroundColor);
    
    if(m_workWindow){
        m_window.draw(*m_workWindow);
    }
    if(m_toolWindow){
        m_window.draw(*m_toolWindow);
    }
    if(m_toolPickerWindow){
        m_window.draw(*m_toolPickerWindow);
    }
    if(m_menu){
        m_window.draw(*m_menu);
    }
    
    m_window.display();
}