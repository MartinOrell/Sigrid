#include "MainWindow.h"

#include "MainWindowConfigContainer.h"

#include "../../Board/BoardDataContainer.h"
#include <SFML/Window/Clipboard.hpp>
#include <iostream>

using namespace sigrid;


MainWindow::MainWindow()
: m_backgroundColor{sf::Color(30,30,30)}
, m_scale{1.f,1.f}
, m_piecePickerToBoardGap{10.f}{}

bool MainWindow::init(const MainWindowConfigContainer& config){
    
    m_window.create(sf::VideoMode({config.windowWidth, config.windowHeight}), config.windowName);
    m_window.setFramerateLimit(60);

    m_fontManagerPtr = std::make_unique<FontManager>();

    m_size = sf::Vector2u{config.windowWidth, config.windowHeight};
    m_tileColorManagerPtr = std::make_unique<ColorManager>(config.tileColors);
    m_arrowColorManagerPtr = std::make_unique<ColorManager>(config.arrowColors);
    m_pieceManagerPtr = std::make_unique<PieceManager>(config.pieceColors);
    m_iconManagerPtr = std::make_unique<IconManager>();

    sigrid::Tool leftClickTool{config.leftClickTool};
    m_inputHandler.addTool(sf::Mouse::Button::Left, std::move(leftClickTool));
    sigrid::Tool rightClickTool{config.rightClickTool};
    m_inputHandler.addTool(sf::Mouse::Button::Right, std::move(rightClickTool));
    sigrid::Tool middleClickTool{config.middleClickTool};
    m_inputHandler.addTool(sf::Mouse::Button::Middle, std::move(middleClickTool));
    sigrid::Tool extra1ClickTool{config.extra1ClickTool};
    m_inputHandler.addTool(sf::Mouse::Button::Extra1, std::move(extra1ClickTool));
    sigrid::Tool extra2ClickTool{config.extra2ClickTool};
    m_inputHandler.addTool(sf::Mouse::Button::Extra2, std::move(extra2ClickTool));

    sigrid::Action spaceBarTool(ActionType::SetTool{sf::Mouse::Button::Left, ToolSelection::Select});
    m_inputHandler.addTool(sf::Keyboard::Key::Space, std::move(spaceBarTool));
    sigrid::Action leftKeyTool(ActionType::OpenLeftBoard{});
    m_inputHandler.addTool(sf::Keyboard::Key::Left, std::move(leftKeyTool));
    sigrid::Action rightKeyTool(ActionType::OpenRightBoard{});
    m_inputHandler.addTool(sf::Keyboard::Key::Right, std::move(rightKeyTool));

    sigrid::Action ctrlNTool(ActionType::NewBoard{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::N, std::move(ctrlNTool));
    sigrid::Action ctrlSTool(ActionType::SaveBoard{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::S, std::move(ctrlSTool));
    sigrid::Action ctrlCTool(ActionType::CopyFen{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::C, std::move(ctrlCTool));
    sigrid::Action ctrlVTool(ActionType::PasteFen{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::V, std::move(ctrlVTool));
    sigrid::Action ctrlLeftKeyTool(ActionType::AddTileColumnLeft{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Left, std::move(ctrlLeftKeyTool));
    sigrid::Action ctrlRightKeyTool(ActionType::AddTileColumnRight{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Right, std::move(ctrlRightKeyTool));
    sigrid::Action ctrlUpKeyTool(ActionType::AddTileRowUp{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Up, std::move(ctrlUpKeyTool));
    sigrid::Action ctrlDownKeyTool(ActionType::AddTileRowDown{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Down, std::move(ctrlDownKeyTool));

    sigrid::Action ctrlShiftLeftKeyTool(ActionType::RemoveTileColumnRight{});
    m_inputHandler.addCtrlShiftTool(sf::Keyboard::Key::Left, std::move(ctrlShiftLeftKeyTool));
    sigrid::Action ctrlShiftRightKeyTool(ActionType::RemoveTileColumnLeft{});
    m_inputHandler.addCtrlShiftTool(sf::Keyboard::Key::Right, std::move(ctrlShiftRightKeyTool));
    sigrid::Action ctrlShiftUpKeyTool(ActionType::RemoveTileRowDown{});
    m_inputHandler.addCtrlShiftTool(sf::Keyboard::Key::Up, std::move(ctrlShiftUpKeyTool));
    sigrid::Action ctrlShiftDownKeyTool(ActionType::RemoveTileRowUp{});
    m_inputHandler.addCtrlShiftTool(sf::Keyboard::Key::Down, std::move(ctrlShiftDownKeyTool));

    m_toolWindow = std::make_unique<sigrid::ToolWindow>();
    m_toolWindow->setTileColorManagerPtr(m_tileColorManagerPtr.get());
    m_toolWindow->setIconManagerPtr(m_iconManagerPtr.get());
    m_toolWindow->setPieceManagerPtr(m_pieceManagerPtr.get());
    m_toolWindow->setArrowColorManagerPtr(m_arrowColorManagerPtr.get());
    m_toolWindow->init();

    m_pieceManagerPtr->loadImages(config.pieces);

    m_toolPickerWindow = std::make_unique<sigrid::ToolPickerWindow>();
    m_toolPickerWindow->setTileColorManagerPtr(m_tileColorManagerPtr.get());
    m_toolPickerWindow->setPieceManagerPtr(m_pieceManagerPtr.get());
    m_toolPickerWindow->setArrowColorManagerPtr(m_arrowColorManagerPtr.get());
    m_toolPickerWindow->setIconManagerPtr(m_iconManagerPtr.get());
    m_toolPickerWindow->init(config.toolPickerData);

    BoardDataContainer boardData;
    if(std::filesystem::exists(config.boardFilename)){
        
        if(boardData.load(config.boardFilename)){
            std:: cout << "Board data: " << config.boardFilename << " loaded" << std::endl;
        }
        else if (boardData.load(config.resetBoardFilename)){
            std::cerr << "Failed reading Board data: " << config.boardFilename << std::endl;
            std::cerr << "Board data: " << config.resetBoardFilename << " loaded instead" << std::endl;
        }
        else{
            std::cerr << "Main Window failed reading both " << config.boardFilename
            << " and " << config.resetBoardFilename << "." << std::endl;
            std::cerr << "Main Window failed creating board." << std::endl;
            return false;
        }
    }
    else if (boardData.load(config.resetBoardFilename)){
        std::cout << "Board data: " << config.resetBoardFilename << " loaded" << std::endl;
    }
    else{
        std::cerr << "Main Window failed reading " << config.resetBoardFilename << std::endl;
        std::cerr << "Main Window failed creating board." << std::endl;
        return false;
    }

    m_workWindow = std::make_unique<sigrid::WorkWindow>();
    m_workWindow->setBoardFilename(config.boardFilename);
    m_workWindow->setDefaultBoardImageFilename(config.defaultBoardImageFilename);
    m_workWindow->setTileColorManagerPtr(m_tileColorManagerPtr.get());
    m_workWindow->setPieceManagerPtr(m_pieceManagerPtr.get());
    m_workWindow->setArrowColorManagerPtr(m_arrowColorManagerPtr.get());
    m_workWindow->setFontManagerPtr(m_fontManagerPtr.get());
    m_workWindow->init(boardData, config.boardData);
    std::cout << "Save location: " << m_workWindow->getSaveFilename() << std::endl;

    m_menu = std::make_unique<sigrid::Menu>();
    m_menu->setFontManagerPtr(m_fontManagerPtr.get());
    m_menu->init(config.menuData);

    if(m_workWindow){
        std::string title = m_workWindow->getName();
        if(title.size() > 0){
            m_window.setTitle(title);
        }
    }

    m_layout.setFromXCoord(LayoutItem::MENU, 0);
    if(m_menu && m_menu->isCollapsed()){
        m_layout.setToXCoord(LayoutItem::MENU, 1);
    }
    else{
        m_layout.setToXCoord(LayoutItem::MENU, 3);
    }

    return true;
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

    {
        //second row x id coordinates

        m_layout.setFromXCoord(LayoutItem::TOOLPICKER, 0);
        m_layout.setToXCoord(LayoutItem::TOOLPICKER, 1);

        if(m_toolPickerWindow && !m_toolPickerWindow->isHidden() ||
        m_toolWindow && !m_toolWindow->isHidden() ||
        m_menu && !m_menu->isPinned()){
            m_layout.setFromXCoord(LayoutItem::WORK, 2);
        }
        else{
            m_layout.setFromXCoord(LayoutItem::WORK, 0);
        }
        m_layout.setToXCoord(LayoutItem::WORK, 3);
    }

    {
        //Third row x id coordinates
        m_layout.setFromXCoord(LayoutItem::TOOLINDICATOR, 0);
        m_layout.setToXCoord(LayoutItem::TOOLINDICATOR, 1);
    }

    {
        //Left column y id coordinates
        m_layout.setFromYCoord(LayoutItem::MENU, 0);
        m_layout.setToYCoord(LayoutItem::MENU, 1);
        if(!m_menu){
            m_layout.setFromYCoord(LayoutItem::TOOLPICKER, 0);
        }
        else{
            m_layout.setFromYCoord(LayoutItem::TOOLPICKER, 1);
        }
        if(m_toolWindow){
            m_layout.setToYCoord(LayoutItem::TOOLPICKER, 2);
        }
        else{
            m_layout.setToYCoord(LayoutItem::TOOLPICKER, 3);
        }
        m_layout.setFromYCoord(LayoutItem::TOOLINDICATOR, 2);
        m_layout.setToYCoord(LayoutItem::TOOLINDICATOR, 3);
    }

    {
        //second column y id coordinates

        if(!m_menu || m_menu->isCollapsed()){
            m_layout.setFromYCoord(LayoutItem::WORK, 0);
        }
        else{
            m_layout.setFromYCoord(LayoutItem::WORK, 1);
        }

        m_layout.setToYCoord(LayoutItem::WORK, 3);
    }

    m_layout.setPx(0, 0.f);
    m_layout.setPx(3, m_size.x);
    m_layout.setPy(0, 0.f);
    m_layout.setPy(3, m_size.y);

    m_layout.setPy(1, 40.f);
    m_layout.setPyIfLess(1, (float)m_size.y/10.f);

    m_layout.setPy(2, m_size.y - 150.f);
    m_layout.setPyIfGreater(2, (float)m_size.y - (float)m_size.y/10.f);

    if(!m_toolPickerWindow || m_toolPickerWindow->isHidden()){
        m_layout.setPx(1, 120.f);
    }
    else{
        unsigned int toolPickerColumns = m_toolPickerWindow->getNumColumns();
        unsigned int toolPickerRows = m_toolPickerWindow->getNumRows();
        unsigned int boardColumns = m_workWindow->getNumColumns();

        auto toolAndWorkWidth_o = m_layout.getWidth(0,3);
        if(toolAndWorkWidth_o != std::nullopt){
            float toolAndWorkWidth = toolAndWorkWidth_o.value();
            float toolRatio = (float)toolPickerColumns/(float)(toolPickerColumns+boardColumns);
            float toolWidth = toolAndWorkWidth * toolRatio;
            m_layout.setPx(1, toolWidth);
        }

        auto toolPickerHeight_o = m_layout.getHeight(1,2);
        if(toolPickerHeight_o != std::nullopt){
            float toolPickerHeight = toolPickerHeight_o.value();
            unsigned int toolPickerTileHeight = toolPickerHeight/toolPickerRows;
            unsigned int toolPickerTileWidth = toolPickerTileHeight;
            m_layout.setPxIfLess(1, toolPickerTileWidth*toolPickerColumns);
            m_layout.setPxIfGreater(1, 120.f);
        }
    }
    m_layout.setPx(2, m_layout.getPx(1) + m_piecePickerToBoardGap);

    if(m_menu){
        auto size_o = m_layout.getSizeU(LayoutItem::MENU);
        auto position_o = m_layout.getPosition(LayoutItem::MENU);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_menu->createGraphic(size_o.value());
            m_menu->setPosition(position_o.value());
        }
    }

    if(m_toolWindow){
        auto size_o = m_layout.getSizeU(LayoutItem::TOOLINDICATOR);
        auto position_o = m_layout.getPosition(LayoutItem::TOOLINDICATOR);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_toolWindow->createGraphic(size_o.value());
            m_toolWindow->setPosition(position_o.value());
        }
    }

    if(m_toolPickerWindow && !(m_toolPickerWindow->isHidden())){
        auto size_o = m_layout.getSizeU(LayoutItem::TOOLPICKER);
        auto position_o = m_layout.getPosition(LayoutItem::TOOLPICKER);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_toolPickerWindow->createGraphic(size_o.value());
            m_toolPickerWindow->setPosition(position_o.value());
        }
    }

    if(m_workWindow){
        auto size_o = m_layout.getSizeU(LayoutItem::WORK);
        auto position_o = m_layout.getPosition(LayoutItem::WORK);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_workWindow->createGraphic(size_o.value());
            m_workWindow->setPosition(position_o.value());
        }
    }
}

void MainWindow::resize(const sf::Vector2u& size){

    sf::FloatRect visibleArea{{0,0},{(float)size.x, (float)size.y}};

    m_window.setView((sf::View)(visibleArea));
    m_size = size;
    createGraphic();
}

void MainWindow::mouseButtonPress(const sf::Vector2i& position, const sf::Mouse::Button& button){

    sf::Vector2f scaledPosition{(m_scale.x*(float)position.x), (m_scale.y*(float)position.y)};

    m_mouse.press(button, scaledPosition);

}

void MainWindow::mouseButtonRelease(const sf::Vector2i& position, const sf::Mouse::Button& button){

    sf::Vector2f scaledPosition{(m_scale.x*(float)position.x), (m_scale.y*(float)position.y)};

    if(m_menu && m_menu->contains(scaledPosition)){
        Action action = m_menu->clicked(scaledPosition);
        handleAction(action);
    }
    else if(m_workWindow && m_workWindow->contains(scaledPosition)){
        sigrid::Tool* usedToolPtr = m_inputHandler.getToolPtr(button);
        Action action = m_workWindow->clicked(*usedToolPtr, m_mouse.getPressPosition(button), scaledPosition);
        handleAction(action);
    }
    else if(m_toolWindow && m_toolWindow->contains(scaledPosition)){
        //Currently clicking inside toolWindow does nothing
    }
    else if(m_toolPickerWindow && m_toolPickerWindow->contains(scaledPosition)){
        sigrid::Tool* usedToolPtr = m_inputHandler.getToolPtr(button);
        Action action = m_toolPickerWindow->clicked(*usedToolPtr, scaledPosition);
        handleAction(action);
    }
    m_mouse.release(button);
}

void MainWindow::keyPress(const sf::Event::KeyPressed& keyboardKeyPressed){

    if(keyboardKeyPressed.control && keyboardKeyPressed.shift){
        auto action_o = m_inputHandler.getCtrlShiftAction(keyboardKeyPressed.code);

        if(action_o == std::nullopt){
            return;
        }
        handleAction(action_o.value());
        return;
    }

    if(keyboardKeyPressed.control){
        auto action_o = m_inputHandler.getCtrlAction(keyboardKeyPressed.code);

        if(action_o == std::nullopt){
            return;
        }
        handleAction(action_o.value());
        return;
    }

    auto action_o = m_inputHandler.getAction(keyboardKeyPressed.code);

    if(action_o == std::nullopt){
        return;
    }

    handleAction(action_o.value());
}

void MainWindow::textEnter(const char32_t& unicode){

    if(!m_workWindow){
        return;
    }
    if(!m_pieceManagerPtr){
        return;
    }

    sf::String text{unicode};
    std::string pieceNotation{text};

    int colorId;
    if(std::isupper(pieceNotation.back())){
        colorId = 0;
    }
    else{
        colorId = 1;
        pieceNotation.back() = std::toupper(pieceNotation.back());
    }

    LogicPiece logicPiece{pieceNotation, colorId};

    if(m_pieceManagerPtr->getGraphicPiece(logicPiece) == std::nullopt){
        return;
    }

    m_workWindow->useAddEntityAtSelectionTool(logicPiece);
}

void MainWindow::mouseMove(const sf::Vector2i& position){

    sf::Vector2f scaledPosition{(m_scale.x*(float)position.x), (m_scale.y*(float)position.y)};

    if(m_workWindow && m_workWindow->contains(scaledPosition)){
        sf::Mouse::Button buttons[5] = {sf::Mouse::Button::Left, sf::Mouse::Button::Right, sf::Mouse::Button::Middle, sf::Mouse::Button::Extra1, sf::Mouse::Button::Extra2};
        for(int i = 0; i < 5; i++){
            sigrid::Tool* usedToolPtr = m_inputHandler.getToolPtr(buttons[i]);
            if(m_mouse.isPressed(buttons[i])){
                m_workWindow->dragMouse(*usedToolPtr, m_mouse.getPressPosition(buttons[i]), scaledPosition);
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
            keyPress(*keyPressed);
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
    else if(std::holds_alternative<ActionType::PickEntity>(action)){
        
        sigrid::LogicEntity logicEntity = std::get<ActionType::PickEntity>(action).logicEntity;
        
        pickEntity(logicEntity);
        return;
    }
    else if(std::holds_alternative<ActionType::PickPieceColor>(action)){

        sigrid::LogicPiece logicPiece = std::get<ActionType::PickPieceColor>(action).logicPiece;
   
        pickPieceColor(logicPiece);
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
    else if(std::holds_alternative<ActionType::PickCircle>(action)){

        int colorId = std::get<ActionType::PickCircle>(action).colorId;
        pickCircle(colorId);
    }
    else if(std::holds_alternative<ActionType::PickCircleColor>(action)){

        int colorId = std::get<ActionType::PickCircleColor>(action).colorId;
        pickCircleColor(colorId);
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
    else if(std::holds_alternative<ActionType::NewBoard>(action)){
        newBoard();
        return;
    }
    else if(std::holds_alternative<ActionType::OpenLeftBoard>(action)){
        openLeftBoard();
        return;
    }
    else if(std::holds_alternative<ActionType::OpenRightBoard>(action)){
        openRightBoard();
        return;
    }
    else if(std::holds_alternative<ActionType::SaveBoard>(action)){
        saveBoard();
        return;
    }
    else if(std::holds_alternative<ActionType::PasteFen>(action)){
        pasteFen();
        return;
    }
    else if(std::holds_alternative<ActionType::CopyFen>(action)){
        copyFen();
        return;
    }
    else if(std::holds_alternative<ActionType::FlipBoard>(action)){
        flipBoard();
        return;
    }
    else if(std::holds_alternative<ActionType::AddLeftInsideLabels>(action)){
        addLeftInsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::AddBottomInsideLabels>(action)){
        addBottomInsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::AddLeftOutsideLabels>(action)){
        addLeftOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::AddRightOutsideLabels>(action)){
        addRightOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::AddTopOutsideLabels>(action)){
        addTopOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::AddBottomOutsideLabels>(action)){
        addBottomOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveLeftInsideLabels>(action)){
        removeLeftInsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveBottomInsideLabels>(action)){
        removeBottomInsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveLeftOutsideLabels>(action)){
        removeLeftOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveRightOutsideLabels>(action)){
        removeRightOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveTopOutsideLabels>(action)){
        removeTopOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveBottomOutsideLabels>(action)){
        removeBottomOutsideLabels();
        return;
    }
    else if(std::holds_alternative<ActionType::SetCoordinateSize>(action)){
        float size = std::get<ActionType::SetCoordinateSize>(action).size;
        setCoordinateSize(size);
        return;
    }
    else if(std::holds_alternative<ActionType::AddTileColumnRight>(action)){
        addTileColumnRight();
        return;
    }
    else if(std::holds_alternative<ActionType::AddTileColumnLeft>(action)){
        addTileColumnLeft();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveTileColumnRight>(action)){
        removeTileColumnRight();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveTileColumnLeft>(action)){
        removeTileColumnLeft();
        return;
    }
    else if(std::holds_alternative<ActionType::AddTileRowUp>(action)){
        addTileRowUp();
        return;
    }
    else if(std::holds_alternative<ActionType::AddTileRowDown>(action)){
        addTileRowDown();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveTileRowUp>(action)){
        removeTileRowUp();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveTileRowDown>(action)){
        removeTileRowDown();
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
    else if(std::holds_alternative<ActionType::AddTurnToken>(action)){
        addTurnToken();
        return;
    }
    else if(std::holds_alternative<ActionType::RemoveTurnToken>(action)){
        removeTurnToken();
        return;
    }
}

void MainWindow::pinMenu(){
    if(!m_menu){
        std::cerr << "Unable to pin menu, Menu does not exist" << std::endl;
        return;
    }

    m_menu->pinMenu();
    m_menu->toggleItem("PinMenu");
    createGraphic();
}

void MainWindow::showMenu(){
    if(!m_menu){
        std::cerr << "Unable to show menu, Menu does not exist" << std::endl;
        return;
    }
    if(m_menu->showMenu()){
        m_layout.setToXCoord(LayoutItem::MENU, 3);
    }
    else{
        m_layout.setToXCoord(LayoutItem::MENU, 1);
    }
    createGraphic();
}

void MainWindow::toggleHeader(const int headerId){
    if(!m_menu){
        std::cerr << "Unable to toggle header, Menu does not exist" << std::endl;
        return;
    }
    m_menu->toggleHeader(headerId);
}

void MainWindow::reset(){
    if(!m_workWindow){
        std::cerr << "Unable to reset board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->reset();
}

void MainWindow::clear(){
    if(!m_workWindow){
        std::cerr << "Unable to clear board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->clear();
}

void MainWindow::print(){
    if(!m_workWindow){
        std::cerr << "Unable to print board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->print();
}

void MainWindow::pickEntity(const sigrid::LogicEntity& logicEntity){
    if(!m_toolWindow){
        std::cerr << "Unable to pick piece, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick piece, toolpicker window does not exist" << std::endl;
        return;
    }
    m_inputHandler.setEntity(sf::Mouse::Button::Left, logicEntity);
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::EntityAdder);
    if(std::holds_alternative<LogicPiece>(logicEntity)){
        m_toolWindow->setSetPieceTool(std::get<LogicPiece>(logicEntity));
        m_toolPickerWindow->setPieceColorTools(std::get<LogicPiece>(logicEntity).getNotation());
    }
    else if(std::holds_alternative<LogicCircle>(logicEntity)){
        LogicCircle circle = std::get<LogicCircle>(logicEntity);
        m_toolWindow->setAddCircleTool(circle.getColorId());
        m_toolPickerWindow->setAddCircleTool(circle.getColorId());
    }
}

void MainWindow::pickPieceColor(const sigrid::LogicPiece& logicPiece){

    if(!m_toolWindow){
        std::cerr << "Unable to pick piece color, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick piece color, toolpicker window does not exist" << std::endl;
        return;
    }

    m_inputHandler.setEntity(sf::Mouse::Button::Left, logicPiece);
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::EntityAdder);
    m_toolWindow->setSetPieceTool(logicPiece);
    m_toolPickerWindow->setPieceTools(logicPiece.getColorId());
}

void MainWindow::pickArrow(const int colorId){
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick arrow, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick arrow color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_inputHandler.setArrow(sf::Mouse::Button::Left, colorId);
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::DrawArrow);
    m_toolWindow->setAddArrowTool(colorId);
    m_toolPickerWindow->setArrowColors();
}

void MainWindow::pickArrowColor(const int colorId){
    if(!m_toolWindow){
        std::cerr << "Unable to pick arrow color, toolWindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick arrow color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_inputHandler.setArrow(sf::Mouse::Button::Left, colorId);
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::DrawArrow);
    m_toolWindow->setAddArrowTool(colorId);
    m_toolPickerWindow->setAddArrowTool(colorId);
}

void MainWindow::pickCircle(const int colorId){
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick circle, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick circle color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_inputHandler.setEntity(sf::Mouse::Button::Left, LogicCircle{colorId});
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::EntityAdder);
    m_toolWindow->setAddCircleTool(colorId);
    m_toolPickerWindow->setCircleColors();
}

void MainWindow::pickCircleColor(const int colorId){
    if(!m_toolWindow){
        std::cerr << "Unable to pick circle color, toolWindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "Unable to pick circle color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_inputHandler.setEntity(sf::Mouse::Button::Left, LogicCircle{colorId});
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::EntityAdder);
    m_toolWindow->setAddCircleTool(colorId);
    m_toolPickerWindow->setAddCircleTool(colorId);
}

void MainWindow::setTool(const sigrid::ToolSelection& selection, const sf::Mouse::Button& button){
    if(!m_toolWindow){
        std::cerr << "Unable to set tool, toolWindow does not exist" << std::endl;
        return;
    }
    m_inputHandler.setSelection(button, selection);
    m_toolWindow->setSelectTool(button, selection);
    if(selection == ToolSelection::Select){
        m_inputHandler.setArrow(button,0);
    }
}

void MainWindow::showColorTools(){

    if(!m_toolPickerWindow){
        std::cerr << "Unable to show color tools, toolpicker window does not exist" << std::endl;
        return;
    }

    m_toolPickerWindow->showColorTools();
    if(m_menu){
        m_menu->toggleItem("ShowColorTools");
        
    }
    
    createGraphic();
}

void MainWindow::hideColorTools(){

    if(!m_toolPickerWindow){
        std::cerr << "Unable to hide color tools, toolpicker window does not exist" << std::endl;
        return;
    }

    m_toolPickerWindow->hideColorTools();
    if(m_menu){
        m_menu->toggleItem("ShowColorTools");
    }

    createGraphic();
}

void MainWindow::showTools(){

    if(!m_toolPickerWindow){
        std::cerr << "Unable to show tools, toolpicker window does not exist" << std::endl;
        return;
    }

    if(!m_toolWindow){
        std::cerr << "Unable to show tools, tool window does not exist" << std::endl;
    }

    m_toolPickerWindow->show();
    m_toolWindow->show();
    if(m_menu){
        m_menu->toggleItem("ShowToolWindow");
        m_menu->showItem("ShowColorTools");
    }
    
    createGraphic();
}

void MainWindow::hideTools(){
    if(!m_toolPickerWindow){
        std::cerr << "Unable to toggle tools, toolpicker window does not exist" << std::endl;
        return;
    }

    if(!m_toolWindow){
        std::cerr << "Unable to toggle tools, tool window does not exist" << std::endl;
    }

    m_toolPickerWindow->hide();
    m_toolWindow->hide();
    if(m_menu){
        m_menu->toggleItem("ShowToolWindow");
        m_menu->hideItem("ShowColorTools");
    }
    
    createGraphic();
}

void MainWindow::newBoard(){

    if(!m_workWindow){
        std::cerr << "Unable to add new board, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->newBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);

}

void MainWindow::openLeftBoard(){
    
    if(!m_workWindow){
        return;
    }

    m_workWindow->openLeftBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::openRightBoard(){

    if(!m_workWindow){
        return;
    }

    m_workWindow->openRightBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::saveBoard(){

    if(!m_workWindow){
        std::cerr << "Unable to save board, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->saveBoard();

}

void MainWindow::pasteFen(){

    if(!m_workWindow){
        std::cerr << "Unable to paste FEN string, workwindow does not exist" << std::endl;
        return;
    }

    std::string fen = std::string(sf::Clipboard::getString());
    m_workWindow->loadFen(fen);
}

void MainWindow::copyFen(){

    if(!m_workWindow){
        std::cerr << "Unable to copy FEN string, workwindow does not exist" << std::endl;
        return;
    }

    std::string fen = m_workWindow->getFen();
    sf::Clipboard::setString(sf::String(fen));
    std::cout << "Copied Fen: \"" << fen << "\"" << std::endl;
}

void MainWindow::flipBoard(){

    if(!m_workWindow){
        std::cerr << "Unable to flip board, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->flipBoard();
}

void MainWindow::addLeftInsideLabels(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add left inside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addLeftInsideLabels();

    if(m_menu){
        m_menu->toggleItem("LeftInsideLabels");
    }

    createGraphic();
}

void MainWindow::addBottomInsideLabels(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add bottom inside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addBottomInsideLabels();

    if(m_menu){
        m_menu->toggleItem("BottomInsideLabels");
    }

    createGraphic();
}

void MainWindow::addLeftOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add left outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addLeftOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("LeftOutsideLabels");
    }

    createGraphic();
}

void MainWindow::addRightOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add right outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addRightOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("RightOutsideLabels");
    }

    createGraphic();
}

void MainWindow::addTopOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add top outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addTopOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("TopOutsideLabels");
    }

    createGraphic();
}

void MainWindow::addBottomOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "Unable to add bottom outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addBottomOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("BottomOutsideLabels");
    }

    createGraphic();
}

void MainWindow::removeLeftInsideLabels(){

    if(!m_workWindow){
        std::cerr << "Unable to remove left inside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeLeftInsideLabels();

    if(m_menu){
        m_menu->toggleItem("LeftInsideLabels");
    }

    createGraphic();
}

void MainWindow::removeBottomInsideLabels(){

    if(!m_workWindow){
        std::cerr << "Unable to remove bottom inside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeBottomInsideLabels();

    if(m_menu){
        m_menu->toggleItem("BottomInsideLabels");
    }

    createGraphic();
}

void MainWindow::removeLeftOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "Unable to remove left outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeLeftOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("LeftOutsideLabels");
    }

    createGraphic();
}

void MainWindow::removeRightOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "Unable to remove right outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeRightOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("RightOutsideLabels");
    }

    createGraphic();
}

void MainWindow::removeTopOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "Unable to remove top outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeTopOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("TopOutsideLabels");
    }

    createGraphic();
}

void MainWindow::removeBottomOutsideLabels(){

    if(!m_workWindow){
        std::cerr << "Unable to remove bottom outside labels, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeBottomOutsideLabels();

    if(m_menu){
        m_menu->toggleItem("BottomOutsideLabels");
    }

    createGraphic();
}

void MainWindow::setCoordinateSize(const float& size){

    if(!m_workWindow){
        std::cerr << "Unable to set coordinate size, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->setCoordinateSize(size);

    if(m_menu){
        m_menu->toggleItem("SetCoordinateSize");
    }

    createGraphic();
}

void MainWindow::addTileColumnRight(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->addTileColumnRight();
    createGraphic();
}

void MainWindow::addTileColumnLeft(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->addTileColumnLeft();
    createGraphic();
}

void MainWindow::removeTileColumnRight(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->removeTileColumnRight();
    createGraphic();
}

void MainWindow::removeTileColumnLeft(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->removeTileColumnLeft();
    createGraphic();
}

void MainWindow::addTileRowUp(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->addTileRowUp();
    createGraphic();
}

void MainWindow::addTileRowDown(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->addTileRowDown();
    createGraphic();
}

void MainWindow::removeTileRowUp(){
    if(!m_workWindow){
        return;
    }
    
    m_workWindow->removeTileRowUp();
    createGraphic();
}

void MainWindow::removeTileRowDown(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->removeTileRowDown();
    createGraphic();
}

void MainWindow::addBoardBorder(){

    if(!m_workWindow){
        std::cerr << "Unable to add border to board, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addBoardBorder();

    if(m_menu){
        m_menu->toggleItem("ToggleBoardBorder");
    }

    createGraphic();
}

void MainWindow::removeBoardBorder(){

    if(!m_workWindow){
        std::cerr << "Unable to remove border to board, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeBoardBorder();

    if(m_menu){
        m_menu->toggleItem("ToggleBoardBorder");
    }

    createGraphic();
}

void MainWindow::addTurnToken(){

    if(!m_workWindow){
        std::cerr << "Unable to add turn token, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addTurnToken();

    if(m_menu){
        m_menu->toggleItem("ToggleAddTurnToken");
    }

    createGraphic();
}

void MainWindow::removeTurnToken(){

    if(!m_workWindow){
        std::cerr << "Unable to remove turn token, workWindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeTurnToken();

    if(m_menu){
        m_menu->toggleItem("ToggleAddTurnToken");
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