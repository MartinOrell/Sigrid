#pragma once

#include <memory>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Tool/Tool.h"
#include "Input/InputHandler.h"
#include "Input/Mouse/Mouse.h"
#include "Config/MainConfigContainer.h"
#include "Layout/LayoutGrid.h"

#include "Menu/Menu.h"
#include "Window/WorkWindow/WorkWindow.h"
#include "Window/ToolWindow/ToolWindow.h"
#include "ToolPicker/ToolPickerWindow.h"

#include "Entity/Icon/IconManager.h"

namespace sigrid{

class MainWindow{

  public:

    MainWindow() = default;
    MainWindow(const MainWindow&) = default;
    MainWindow(MainWindow&&) = default;
    MainWindow& operator=(const MainWindow&) = default;
    MainWindow& operator=(MainWindow&&) = default;

    bool load(const sigrid_config::MainConfigContainer& config);
    void run();

  private:

    void createGraphic();
    
    void handleEvents();
    void resize(const sf::Vector2i& size);
    void mouseButtonPress(const sf::Vector2i& position, const sf::Mouse::Button& button);
    void mouseButtonRelease(const sf::Vector2i& position, const sf::Mouse::Button& button);
    void keyPress(const sf::Event::KeyPressed& keyboardKeyPressed);
    void textEnter(const char32_t& unicode);
    void mouseMove(const sf::Vector2i& position);

    void handleAction(const sigrid_action::Action action);

    void pinMenu();
    void unPinMenu();
    void showMenu();
    void hideMenu();
    void toggleHeader(const int headerId);
    void reset();
    void clear();
    void print();
    void pickEntity(const sigrid::LogicEntity& logicEntity);
    void pickPieceColor(const sigrid::LogicPiece& logicPiece);
    void pickArrow(const int colorId);
    void pickArrowColor(const int colorId);
    void pickCircle(const int colorId);
    void pickCircleColor(const int colorId);
    void setTool(const sigrid::ToolSelection& selection, const sf::Mouse::Button& button);
    void showColorTools();
    void hideColorTools();
    void showTools();
    void hideTools();
    void newBoard();
    void addBoardColumn();
    void removeBoardColumn();
    void addBoardRow();
    void removeBoardRow();
    void shiftBoardsLeft();
    void shiftBoardsRight();
    void gotoRightBoard();
    void gotoLeftBoard();
    void gotoUpBoard();
    void gotoDownBoard();
    void saveBoard();
    void savePdf();
    void pasteFen();
    void copyFen();
    void flipBoard();
    void addLeftInsideLabels();
    void addBottomInsideLabels();
    void addLeftOutsideLabels();
    void addRightOutsideLabels();
    void addTopOutsideLabels();
    void addBottomOutsideLabels();
    void removeLeftInsideLabels();
    void removeBottomInsideLabels();
    void removeLeftOutsideLabels();
    void removeRightOutsideLabels();
    void removeTopOutsideLabels();
    void removeBottomOutsideLabels();
    void setCoordinateSize(const float& size);
    void addTileColumnRight();
    void addTileColumnLeft();
    void removeRightTileColumn();
    void removeLeftTileColumn();
    void addTileRowUp();
    void addTileRowDown();
    void removeTopTileRow();
    void removeBottomTileRow();
    void addBoardBorder();
    void removeBoardBorder();
    void addTurnToken();
    void removeTurnToken();

    void redraw();

    enum LayoutItem{
        MENU,
        WORK,
        TOOLINDICATOR,
        TOOLPICKER,
    };

    sf::RenderWindow m_window;
    sf::Color m_backgroundColor{sf::Color(30,30,30)};
    sf::Vector2i m_size;
    sf::Vector2f m_scale{1.f,1.f};
    float m_piecePickerToBoardGap{10.f};

    LayoutGrid m_layout;
    std::unique_ptr<Menu> m_menu;
    std::unique_ptr<WorkWindow> m_workWindow;
    std::unique_ptr<ToolWindow> m_toolWindow;
    std::unique_ptr<ToolPickerWindow> m_toolPickerWindow;

    sigrid::InputHandler m_inputHandler;

    sigrid::Mouse m_mouse;

    std::unique_ptr<FontManager> m_fontManagerPtr;
    std::unique_ptr<ColorManager> m_tileColorManagerPtr;
    std::unique_ptr<ColorManager> m_arrowColorManagerPtr;
    std::unique_ptr<PieceManager> m_pieceManagerPtr;
    std::unique_ptr<IconManager> m_iconManagerPtr;
};

}  // namespace sigrid