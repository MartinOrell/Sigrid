#include "Window/MainWindow/MainWindow.h"

#include <iostream>

#include <SFML/Window/Clipboard.hpp>

#include "Board/BoardDataContainer.h"
#include "Board/BoardDesignContainer.h"
#include "Menu/MenuContainer.h"
#include "ToolPicker/ToolPickerContainer.h"

using namespace sigrid;

bool MainWindow::load(const sigrid_config::MainConfigContainer& config){
    
    m_window.create(sf::VideoMode({(unsigned int)config.mainWindow.width, (unsigned int)config.mainWindow.height}), config.mainWindow.name);
    m_window.setFramerateLimit(60);

    m_fontManagerPtr = std::make_unique<FontManager>();

    m_size = sf::Vector2i{config.mainWindow.width, config.mainWindow.height};
    m_tileColorManagerPtr = std::make_unique<ColorManager>();
    m_tileColorManagerPtr->setColors(config.tileColors);
    m_arrowColorManagerPtr = std::make_unique<ColorManager>();
    m_arrowColorManagerPtr->setColors(config.arrowColors);
    m_pieceManagerPtr = std::make_unique<PieceManager>();
    m_pieceManagerPtr->setPieceColors(config.pieceColors);
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

    sigrid_action::Action spaceBarTool(sigrid_action::SetTool{sf::Mouse::Button::Left, ToolSelection::Select});
    m_inputHandler.addTool(sf::Keyboard::Key::Space, std::move(spaceBarTool));
    sigrid_action::Action leftKeyTool(sigrid_action::GotoLeftBoard{});
    m_inputHandler.addTool(sf::Keyboard::Key::Left, std::move(leftKeyTool));
    sigrid_action::Action rightKeyTool(sigrid_action::GotoRightBoard{});
    m_inputHandler.addTool(sf::Keyboard::Key::Right, std::move(rightKeyTool));
    sigrid_action::Action upKeyTool(sigrid_action::GotoUpBoard{});
    m_inputHandler.addTool(sf::Keyboard::Key::Up, std::move(upKeyTool));
    sigrid_action::Action downKeyTool(sigrid_action::GotoDownBoard{});
    m_inputHandler.addTool(sf::Keyboard::Key::Down, std::move(downKeyTool));

    sigrid_action::Action ctrlNTool(sigrid_action::NewBoard{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::N, std::move(ctrlNTool));
    sigrid_action::Action ctrlSTool(sigrid_action::SaveBoard{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::S, std::move(ctrlSTool));
    sigrid_action::Action ctrlCTool(sigrid_action::CopyFen{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::C, std::move(ctrlCTool));
    sigrid_action::Action ctrlVTool(sigrid_action::PasteFen{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::V, std::move(ctrlVTool));
    sigrid_action::Action ctrlLeftKeyTool(sigrid_action::AddTileColumnLeft{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Left, std::move(ctrlLeftKeyTool));
    sigrid_action::Action ctrlRightKeyTool(sigrid_action::AddTileColumnRight{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Right, std::move(ctrlRightKeyTool));
    sigrid_action::Action ctrlUpKeyTool(sigrid_action::AddTileRowUp{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Up, std::move(ctrlUpKeyTool));
    sigrid_action::Action ctrlDownKeyTool(sigrid_action::AddTileRowDown{});
    m_inputHandler.addCtrlTool(sf::Keyboard::Key::Down, std::move(ctrlDownKeyTool));

    sigrid_action::Action ctrlShiftLeftKeyTool(sigrid_action::RemoveRightTileColumn{});
    m_inputHandler.addCtrlShiftTool(sf::Keyboard::Key::Left, std::move(ctrlShiftLeftKeyTool));
    sigrid_action::Action ctrlShiftRightKeyTool(sigrid_action::RemoveLeftTileColumn{});
    m_inputHandler.addCtrlShiftTool(sf::Keyboard::Key::Right, std::move(ctrlShiftRightKeyTool));
    sigrid_action::Action ctrlShiftUpKeyTool(sigrid_action::RemoveBottomTileRow{});
    m_inputHandler.addCtrlShiftTool(sf::Keyboard::Key::Up, std::move(ctrlShiftUpKeyTool));
    sigrid_action::Action ctrlShiftDownKeyTool(sigrid_action::RemoveTopTileRow{});
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
    m_toolPickerWindow->load(config.toolPickerData);

    BoardDataContainer boardData;
    if(std::filesystem::exists(config.boardFilename)){
        
        if(boardData.load(config.boardFilename)){
            std:: cout << "Board data: " << config.boardFilename << " loaded" << std::endl;
        }
        else if (boardData.load(config.resetBoardFilename)){
            std::cerr << "MainWindow: Failed reading Board data: " << config.boardFilename << std::endl;
            std::cerr << "Board data: " << config.resetBoardFilename << " loaded instead" << std::endl;
        }
        else{
            std::cerr << "MainWindow: Failed reading both " << config.boardFilename
            << " and " << config.resetBoardFilename << "." << std::endl;
            std::cerr << "Main Window failed creating board." << std::endl;
            return false;
        }
    }
    else if (boardData.load(config.resetBoardFilename)){
        std::cout << "Board data: " << config.resetBoardFilename << " loaded" << std::endl;
    }
    else{
        std::cerr << "MainWindow: Failed reading " << config.resetBoardFilename << std::endl;
        std::cerr << "MainWindow: Failed creating board." << std::endl;
        return false;
    }

    m_workWindow = std::make_unique<sigrid::WorkWindow>();
    m_workWindow->setBoardFilename(config.boardFilename);
    m_workWindow->setResetBoardFilename(config.resetBoardFilename);
    m_workWindow->setDefaultBoardImageFilename(config.defaultBoardImageFilename);
    m_workWindow->setTileColorManagerPtr(m_tileColorManagerPtr.get());
    m_workWindow->setPieceManagerPtr(m_pieceManagerPtr.get());
    m_workWindow->setArrowColorManagerPtr(m_arrowColorManagerPtr.get());
    m_workWindow->setFontManagerPtr(m_fontManagerPtr.get());
    m_workWindow->loadGraphicData(config.boardData);
    m_workWindow->loadBoardData(boardData);
    std::cout << "Save location: " << m_workWindow->getSaveFilename() << std::endl;

    m_menu = std::make_unique<sigrid::Menu>();
    m_menu->setFontManagerPtr(m_fontManagerPtr.get());
    m_menu->load(config.menuData);

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
    m_layout.setFromYCoord(LayoutItem::MENU, 0);
    m_layout.setToYCoord(LayoutItem::MENU, 1);

    m_layout.setFromXCoord(LayoutItem::TOOLPICKER, 0);
    m_layout.setToXCoord(LayoutItem::TOOLPICKER, 1);
    if(m_menu){
        m_layout.setFromYCoord(LayoutItem::TOOLPICKER, 1);
    }
    else{
        m_layout.setFromYCoord(LayoutItem::TOOLPICKER, 0);
    }
    if(m_toolWindow){
        m_layout.setToYCoord(LayoutItem::TOOLPICKER, 2);
    }
    else{
        m_layout.setToYCoord(LayoutItem::TOOLPICKER, 3);
    }

    if(m_toolPickerWindow && m_toolPickerWindow->isVisible() ||
    m_toolWindow && m_toolWindow->isVisible() ||
    m_menu && !m_menu->isPinned()){
        m_layout.setFromXCoord(LayoutItem::WORK, 2);
    }
    else{
        m_layout.setFromXCoord(LayoutItem::WORK, 0);
    }
    m_layout.setToXCoord(LayoutItem::WORK, 3);

    if(!m_menu || m_menu->isCollapsed()){
        m_layout.setFromYCoord(LayoutItem::WORK, 0);
    }
    else{
        m_layout.setFromYCoord(LayoutItem::WORK, 1);
    }
    m_layout.setToYCoord(LayoutItem::WORK, 3);

    m_layout.setFromXCoord(LayoutItem::TOOLINDICATOR, 0);
    m_layout.setToXCoord(LayoutItem::TOOLINDICATOR, 1);
    m_layout.setFromYCoord(LayoutItem::TOOLINDICATOR, 2);
    m_layout.setToYCoord(LayoutItem::TOOLINDICATOR, 3);

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
        int toolPickerColumns = m_toolPickerWindow->getNumColumns();
        int toolPickerRows = m_toolPickerWindow->getNumRows();
        int boardColumns = m_workWindow->getNumColumns();

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
            int toolPickerTileHeight = toolPickerHeight/toolPickerRows;
            int toolPickerTileWidth = toolPickerTileHeight;
            m_layout.setPxIfLess(1, toolPickerTileWidth*toolPickerColumns);
            m_layout.setPxIfGreater(1, 120.f);
        }
    }

    {
        auto px1_o = m_layout.getPx(1);
        if(px1_o != std::nullopt){
            float px1 = px1_o.value();
            float px2 = px1 + m_piecePickerToBoardGap;
            m_layout.setPx(2, px2);
        }
    }

    if(m_menu){
        auto size_o = m_layout.getSize(LayoutItem::MENU);
        auto position_o = m_layout.getTopLeftPosition(LayoutItem::MENU);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_menu->createGraphic(size_o.value());
            m_menu->setPosition(position_o.value());
        }
    }

    if(m_toolWindow){
        auto size_o = m_layout.getSize(LayoutItem::TOOLINDICATOR);
        auto position_o = m_layout.getTopLeftPosition(LayoutItem::TOOLINDICATOR);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_toolWindow->createGraphic(size_o.value());
            m_toolWindow->setPosition(position_o.value());
        }
    }

    if(m_toolPickerWindow && m_toolPickerWindow->isVisible()){
        auto size_o = m_layout.getSize(LayoutItem::TOOLPICKER);
        auto position_o = m_layout.getTopLeftPosition(LayoutItem::TOOLPICKER);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_toolPickerWindow->createGraphic(size_o.value());
            m_toolPickerWindow->setPosition(position_o.value());
        }
    }

    if(m_workWindow){
        auto size_o = m_layout.getSize(LayoutItem::WORK);
        auto position_o = m_layout.getTopLeftPosition(LayoutItem::WORK);
        if(size_o != std::nullopt && position_o != std::nullopt){
            m_workWindow->createGraphic(size_o.value());
            m_workWindow->setPosition(position_o.value());
        }
    }
}

void MainWindow::resize(const sf::Vector2i& size){

    sf::FloatRect visibleArea{{0,0},{(float)size.x, (float)size.y}};

    m_window.setView((sf::View)(visibleArea));
    m_size = size;
    createGraphic();
}

void MainWindow::mouseButtonPress(const sf::Vector2i& position, const sf::Mouse::Button& button){

    sf::Vector2f scaledPosition{(m_scale.x*(float)position.x), (m_scale.y*(float)position.y)};

    m_mouse.press(button, scaledPosition);

    if(m_workWindow && m_workWindow->contains(scaledPosition)){
        m_workWindow->mousePress(scaledPosition);
        m_window.setTitle(m_workWindow->getName());
    }
}

void MainWindow::mouseButtonRelease(const sf::Vector2i& position, const sf::Mouse::Button& button){

    sf::Vector2f scaledPosition{(m_scale.x*(float)position.x), (m_scale.y*(float)position.y)};

    if(m_menu && m_menu->contains(scaledPosition)){
        auto action_o = m_menu->clicked(scaledPosition);
        if(action_o != std::nullopt){
            auto& action = action_o.value();
            handleAction(action);
        }
    }
    else if(m_workWindow && m_workWindow->contains(scaledPosition)){

        auto pressPosition_o = m_mouse.getPressPosition(button);
        if(pressPosition_o != std::nullopt){
            auto& pressPosition = pressPosition_o.value().get();

            auto usedToolPtr_o = m_inputHandler.getToolPtr(button);
            if(usedToolPtr_o != std::nullopt){

                Tool* usedToolPtr = usedToolPtr_o.value();
                auto action_o = m_workWindow->clicked(*usedToolPtr, pressPosition, scaledPosition);
                if(action_o != std::nullopt){
                    auto& action = action_o.value();
                    handleAction(action);
                }
                m_window.setTitle(m_workWindow->getName());
            }
        }
    }
    else if(m_toolWindow && m_toolWindow->contains(scaledPosition)){
        //Currently clicking inside toolWindow does nothing
    }
    else if(m_toolPickerWindow && m_toolPickerWindow->contains(scaledPosition)){

        auto usedToolPtr_o = m_inputHandler.getToolPtr(button);
        if(usedToolPtr_o != std::nullopt){
            Tool* usedToolPtr = usedToolPtr_o.value();
            auto action_o = m_toolPickerWindow->clicked(*usedToolPtr, scaledPosition);
            if(action_o != std::nullopt){
                auto& action = action_o.value();
                handleAction(action);
            }
        }
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

    LogicPiece logicPiece;
    logicPiece.setNotation(pieceNotation);
    logicPiece.setColorId(colorId);

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

            auto usedToolPtr_o = m_inputHandler.getToolPtr(buttons[i]);
            if(usedToolPtr_o == std::nullopt){
                continue;
            }
            Tool* usedToolPtr = usedToolPtr_o.value();

            if(m_mouse.isPressed(buttons[i])){
                auto pressPosition_o = m_mouse.getPressPosition(buttons[i]);
                if(pressPosition_o != std::nullopt){
                    auto& pressPosition = pressPosition_o.value().get();
                    m_workWindow->dragMouse(*usedToolPtr, pressPosition, scaledPosition);
                }
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
            const sf::Vector2u& newSizeU = resized->size;
            const sf::Vector2i& newSize{(int)newSizeU.x, (int)newSizeU.y};
            resize(newSize);
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

void MainWindow::handleAction(const sigrid_action::Action action){

    if(std::holds_alternative<sigrid_action::PinMenu>(action)){
        pinMenu();
        return;
    }
    else if(std::holds_alternative<sigrid_action::UnPinMenu>(action)){
        unPinMenu();
        return;
    }
    else if(std::holds_alternative<sigrid_action::ShowMenu>(action)){
        showMenu();
        return;
    }
    else if(std::holds_alternative<sigrid_action::HideMenu>(action)){
        hideMenu();
        return;
    }
    else if(std::holds_alternative<sigrid_action::ToggleHeader>(action)){
        int headerId = std::get<sigrid_action::ToggleHeader>(action).headerId;
        toggleHeader(headerId);
    }
    else if(std::holds_alternative<sigrid_action::Reset>(action)){
        reset();
        return;
    }
    else if(std::holds_alternative<sigrid_action::Clear>(action)){
        clear();
        return;
    }
    else if(std::holds_alternative<sigrid_action::Print>(action)){
        print();
        return;
    }
    else if(std::holds_alternative<sigrid_action::PickEntity>(action)){
        
        sigrid::LogicEntity logicEntity = std::get<sigrid_action::PickEntity>(action).logicEntity;
        
        pickEntity(logicEntity);
        return;
    }
    else if(std::holds_alternative<sigrid_action::PickPieceColor>(action)){

        sigrid::LogicPiece logicPiece = std::get<sigrid_action::PickPieceColor>(action).logicPiece;
   
        pickPieceColor(logicPiece);
        return;
    }
    else if(std::holds_alternative<sigrid_action::PickArrow>(action)){

        int colorId = std::get<sigrid_action::PickArrow>(action).colorId;
        pickArrow(colorId);
        return;
    }
    else if(std::holds_alternative<sigrid_action::PickArrowColor>(action)){
        
        int colorId = std::get<sigrid_action::PickArrowColor>(action).colorId;
        pickArrowColor(colorId);
        return;
    }
    else if(std::holds_alternative<sigrid_action::PickCircle>(action)){

        int colorId = std::get<sigrid_action::PickCircle>(action).colorId;
        pickCircle(colorId);
    }
    else if(std::holds_alternative<sigrid_action::PickCircleColor>(action)){

        int colorId = std::get<sigrid_action::PickCircleColor>(action).colorId;
        pickCircleColor(colorId);
    }
    else if(std::holds_alternative<sigrid_action::SetTool>(action)){
        
        sigrid_action::SetTool a = std::get<sigrid_action::SetTool>(action);
        setTool(a.selection, a.button);
        return;
    }
    else if(std::holds_alternative<sigrid_action::ShowColorTools>(action)){
        showColorTools();
        return;
    }
    else if(std::holds_alternative<sigrid_action::HideColorTools>(action)){
        hideColorTools();
        return;
    }
    else if(std::holds_alternative<sigrid_action::ShowTools>(action)){
        showTools();
        return;
    }
    else if(std::holds_alternative<sigrid_action::HideTools>(action)){
        hideTools();
        return;
    }
    else if(std::holds_alternative<sigrid_action::NewBoard>(action)){
        newBoard();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddBoardColumn>(action)){
        addBoardColumn();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveBoardColumn>(action)){
        removeBoardColumn();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddBoardRow>(action)){
        addBoardRow();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveBoardRow>(action)){
        removeBoardRow();
        return;
    }
    else if(std::holds_alternative<sigrid_action::ShiftBoardsLeft>(action)){
        shiftBoardsLeft();
        return;
    }
    else if(std::holds_alternative<sigrid_action::ShiftBoardsRight>(action)){
        shiftBoardsRight();
        return;
    }
    else if(std::holds_alternative<sigrid_action::GotoLeftBoard>(action)){
        gotoLeftBoard();
        return;
    }
    else if(std::holds_alternative<sigrid_action::GotoRightBoard>(action)){
        gotoRightBoard();
        return;
    }
    else if(std::holds_alternative<sigrid_action::GotoUpBoard>(action)){
        gotoUpBoard();
        return;
    }
    else if(std::holds_alternative<sigrid_action::GotoDownBoard>(action)){
        gotoDownBoard();
        return;
    }
    else if(std::holds_alternative<sigrid_action::SaveBoard>(action)){
        saveBoard();
        return;
    }
    else if(std::holds_alternative<sigrid_action::SavePdf>(action)){
        savePdf();
        return;
    }
    else if(std::holds_alternative<sigrid_action::PasteFen>(action)){
        pasteFen();
        return;
    }
    else if(std::holds_alternative<sigrid_action::CopyFen>(action)){
        copyFen();
        return;
    }
    else if(std::holds_alternative<sigrid_action::FlipBoard>(action)){
        flipBoard();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddLeftInsideLabels>(action)){
        addLeftInsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddBottomInsideLabels>(action)){
        addBottomInsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddLeftOutsideLabels>(action)){
        addLeftOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddRightOutsideLabels>(action)){
        addRightOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddTopOutsideLabels>(action)){
        addTopOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddBottomOutsideLabels>(action)){
        addBottomOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveLeftInsideLabels>(action)){
        removeLeftInsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveBottomInsideLabels>(action)){
        removeBottomInsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveLeftOutsideLabels>(action)){
        removeLeftOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveRightOutsideLabels>(action)){
        removeRightOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveTopOutsideLabels>(action)){
        removeTopOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveBottomOutsideLabels>(action)){
        removeBottomOutsideLabels();
        return;
    }
    else if(std::holds_alternative<sigrid_action::SetCoordinateSize>(action)){
        float size = std::get<sigrid_action::SetCoordinateSize>(action).size;
        setCoordinateSize(size);
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddTileColumnRight>(action)){
        addTileColumnRight();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddTileColumnLeft>(action)){
        addTileColumnLeft();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveRightTileColumn>(action)){
        removeRightTileColumn();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveLeftTileColumn>(action)){
        removeLeftTileColumn();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddTileRowUp>(action)){
        addTileRowUp();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddTileRowDown>(action)){
        addTileRowDown();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveTopTileRow>(action)){
        removeTopTileRow();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveBottomTileRow>(action)){
        removeBottomTileRow();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddBoardBorder>(action)){
        addBoardBorder();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveBoardBorder>(action)){
        removeBoardBorder();
        return;
    }
    else if(std::holds_alternative<sigrid_action::AddTurnToken>(action)){
        addTurnToken();
        return;
    }
    else if(std::holds_alternative<sigrid_action::RemoveTurnToken>(action)){
        removeTurnToken();
        return;
    }
}

void MainWindow::pinMenu(){
    if(!m_menu){
        std::cerr << "MainWindow: Unable to pin menu, Menu does not exist" << std::endl;
        return;
    }

    m_menu->pinMenu();
    if(!(m_toolPickerWindow && m_toolPickerWindow->isVisible() ||
    m_toolWindow && m_toolWindow->isVisible())){
        m_layout.setFromXCoord(LayoutItem::WORK, 0);
    }

    m_menu->toggleItem("PinMenu");
    createGraphic();
}

void MainWindow::unPinMenu(){
    if(!m_menu){
        std::cerr << "MainWindow: Unable to unpin menu, Menu does not exist" << std::endl;
        return;
    }

    m_menu->unPinMenu();
    m_layout.setFromXCoord(LayoutItem::WORK, 2);

    m_menu->toggleItem("PinMenu");
    createGraphic();
}

void MainWindow::showMenu(){
    if(!m_menu){
        std::cerr << "MainWindow: Unable to show menu, Menu does not exist" << std::endl;
        return;
    }

    m_menu->showMenu();
    m_layout.setToXCoord(LayoutItem::MENU, 3);
    m_layout.setFromYCoord(LayoutItem::WORK, 1);
    createGraphic();
}

void MainWindow::hideMenu(){
    if(!m_menu){
        std::cerr << "MainWindow: Unable to hide menu, Menu does not exist" << std::endl;
        return;
    }

    m_menu->hideMenu();
    m_layout.setToXCoord(LayoutItem::MENU, 1);
    m_layout.setFromYCoord(LayoutItem::WORK, 0);
    createGraphic();
}

void MainWindow::toggleHeader(const int headerId){
    if(!m_menu){
        std::cerr << "MainWindow: Unable to toggle header, Menu does not exist" << std::endl;
        return;
    }
    m_menu->toggleHeader(headerId);
}

void MainWindow::reset(){
    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to reset board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->reset();
    createGraphic();
}

void MainWindow::clear(){
    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to clear board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->clear();
}

void MainWindow::print(){
    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to print board, workWindow does not exist" << std::endl;
        return;
    }
    m_workWindow->print();
}

void MainWindow::pickEntity(const sigrid::LogicEntity& logicEntity){
    if(!m_toolWindow){
        std::cerr << "MainWindow: Unable to pick piece, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick piece, toolpicker window does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to pick piece color, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick piece color, toolpicker window does not exist" << std::endl;
        return;
    }

    m_inputHandler.setEntity(sf::Mouse::Button::Left, logicPiece);
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::EntityAdder);
    m_toolWindow->setSetPieceTool(logicPiece);
    m_toolPickerWindow->setPieceTools(logicPiece.getColorId());
}

void MainWindow::pickArrow(const int colorId){
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick arrow, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick arrow color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_inputHandler.setArrow(sf::Mouse::Button::Left, colorId);
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::DrawArrow);
    m_toolWindow->setAddArrowTool(colorId);
    m_toolPickerWindow->setArrowColors();
}

void MainWindow::pickArrowColor(const int colorId){
    if(!m_toolWindow){
        std::cerr << "MainWindow: Unable to pick arrow color, toolWindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick arrow color, toolpicker window does not exist" << std::endl;
        return;
    }
    m_inputHandler.setArrow(sf::Mouse::Button::Left, colorId);
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::DrawArrow);
    m_toolWindow->setAddArrowTool(colorId);
    m_toolPickerWindow->setAddArrowTool(colorId);
}

void MainWindow::pickCircle(const int colorId){
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick circle, toolwindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick circle color, toolpicker window does not exist" << std::endl;
        return;
    }
    LogicCircle logicCircle;
    logicCircle.setColor(colorId);
    m_inputHandler.setEntity(sf::Mouse::Button::Left, std::move(logicCircle));
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::EntityAdder);
    m_toolWindow->setAddCircleTool(colorId);
    m_toolPickerWindow->setCircleColors();
}

void MainWindow::pickCircleColor(const int colorId){
    if(!m_toolWindow){
        std::cerr << "MainWindow: Unable to pick circle color, toolWindow does not exist" << std::endl;
        return;
    }
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to pick circle color, toolpicker window does not exist" << std::endl;
        return;
    }
    LogicCircle logicCircle;
    logicCircle.setColor(colorId);
    m_inputHandler.setEntity(sf::Mouse::Button::Left, std::move(logicCircle));
    m_inputHandler.setSelection(sf::Mouse::Button::Left, ToolSelection::EntityAdder);
    m_toolWindow->setAddCircleTool(colorId);
    m_toolPickerWindow->setAddCircleTool(colorId);
}

void MainWindow::setTool(const sigrid::ToolSelection& selection, const sf::Mouse::Button& button){
    if(!m_toolWindow){
        std::cerr << "MainWindow: Unable to set tool, toolWindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to show color tools, toolpicker window does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to hide color tools, toolpicker window does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to show tools, toolpicker window does not exist" << std::endl;
        return;
    }

    if(!m_toolWindow){
        std::cerr << "MainWindow: Unable to show tools, tool window does not exist" << std::endl;
    }

    m_toolPickerWindow->show();
    m_toolWindow->show();
    if(m_menu){
        m_menu->toggleItem("ShowToolWindow");
        m_menu->showItem("ShowColorTools");
    }

    m_layout.setFromXCoord(LayoutItem::WORK, 2);
    
    createGraphic();
}

void MainWindow::hideTools(){
    if(!m_toolPickerWindow){
        std::cerr << "MainWindow: Unable to toggle tools, toolpicker window does not exist" << std::endl;
        return;
    }

    if(!m_toolWindow){
        std::cerr << "MainWindow: Unable to toggle tools, tool window does not exist" << std::endl;
    }

    m_toolPickerWindow->hide();
    m_toolWindow->hide();
    if(m_menu){
        m_menu->toggleItem("ShowToolWindow");
        m_menu->hideItem("ShowColorTools");

        if(m_menu->isPinned()){
            m_layout.setFromXCoord(LayoutItem::WORK, 0);
        }
    }
    
    createGraphic();
}

void MainWindow::newBoard(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add new board, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->newBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);

}

void MainWindow::addBoardColumn(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add board column, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addBoardColumn();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::removeBoardColumn(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to remove board column, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeBoardColumn();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::addBoardRow(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add board row, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->addBoardRow();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::removeBoardRow(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to remove board row, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->removeBoardRow();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::shiftBoardsLeft(){
    
    if(!m_workWindow){
        return;
    }

    m_workWindow->shiftBoardsLeft();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::shiftBoardsRight(){

    if(!m_workWindow){
        return;
    }

    m_workWindow->shiftBoardsRight();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::gotoRightBoard(){

    if(!m_workWindow){
        return;
    }

    m_workWindow->gotoRightBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::gotoLeftBoard(){

    if(!m_workWindow){
        return;
    }

    m_workWindow->gotoLeftBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::gotoUpBoard(){

    if(!m_workWindow){
        return;
    }

    m_workWindow->gotoUpBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::gotoDownBoard(){

    if(!m_workWindow){
        return;
    }

    m_workWindow->gotoDownBoard();
    std::string title = m_workWindow->getName();
    m_window.setTitle(title);
}

void MainWindow::saveBoard(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to save board, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->saveBoard();

}

void MainWindow::savePdf(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to save pdf, workwindow does not exist" << std::endl;
        return;
    }

    m_workWindow->savePdf();
}

void MainWindow::pasteFen(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to paste FEN string, workwindow does not exist" << std::endl;
        return;
    }

    std::string fen = std::string(sf::Clipboard::getString());
    m_workWindow->loadFen(fen);
}

void MainWindow::copyFen(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to copy FEN string, workwindow does not exist" << std::endl;
        return;
    }

    std::string fen = m_workWindow->getFen();
    sf::Clipboard::setString(sf::String(fen));
    std::cout << "Copied Fen: \"" << fen << "\"" << std::endl;
}

void MainWindow::flipBoard(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to flip board, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to add bottom outside labels, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove left inside labels, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove bottom inside labels, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove left outside labels, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove right outside labels, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove top outside labels, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove bottom outside labels, workwindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to set coordinate size, workWindow does not exist" << std::endl;
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

void MainWindow::removeRightTileColumn(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->removeRightTileColumn();
    createGraphic();
}

void MainWindow::removeLeftTileColumn(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->removeLeftTileColumn();
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

void MainWindow::removeTopTileRow(){
    if(!m_workWindow){
        return;
    }
    
    m_workWindow->removeTopTileRow();
    createGraphic();
}

void MainWindow::removeBottomTileRow(){
    if(!m_workWindow){
        return;
    }

    m_workWindow->removeBottomTileRow();
    createGraphic();
}

void MainWindow::addBoardBorder(){

    if(!m_workWindow){
        std::cerr << "MainWindow: Unable to add border to board, workWindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove border to board, workWindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to add turn token, workWindow does not exist" << std::endl;
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
        std::cerr << "MainWindow: Unable to remove turn token, workWindow does not exist" << std::endl;
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
        m_workWindow->updateTexture();
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