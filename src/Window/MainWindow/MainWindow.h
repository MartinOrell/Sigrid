#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

#include "../../Menu/Menu.h"
#include "../WorkWindow/WorkWindow.h"
#include "../ToolWindow/ToolWindow.h"
#include "../../ToolPicker/ToolPickerWindow.h"

#include "../../Tool/Tool.h"
#include "MainWindowConfigContainer.h"

namespace sigrid{
    class MainWindow{
        public:
            MainWindow();
            bool init(const MainWindowConfigContainer& config);
            void run();
        private:
            void createGraphic();
            
            void handleEvents();
            void resize(const sf::Vector2u& size);
            void mouseButtonPress(const sf::Vector2i& position, const sf::Mouse::Button& button);
            void mouseButtonRelease(const sf::Vector2i& position, const sf::Mouse::Button& button);
            void keyPress(const sf::Keyboard::Key& keyboardKey);
            void textEnter(const char32_t& unicode);
            void mouseMove(const sf::Vector2i& position);

            void handleAction(const sigrid::Action action);

            void pinMenu();
            void showMenu();
            void toggleHeader(const int headerId);
            void reset();
            void clear();
            void print();
            void pickEntity(const sigrid::LogicEntity& logicEntity, const sigrid::GraphicEntity& graphicEntity);
            void pickPieceColor(const sigrid::LogicPiece& logicPiece, const sigrid::GraphicPiece& graphicPiece);
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
            void openLeftBoard();
            void openRightBoard();
            void saveBoard();
            void pasteFen();
            void copyFen();
            void flipBoard();
            void addCoordinates();
            void removeCoordinates();
            void moveCoordinatesOutside();
            void moveCoordinatesInside();
            void setCoordinateSize(const float& size);
            void addSquareColumnRight();
            void addSquareColumnLeft();
            void removeSquareColumnRight();
            void removeSquareColumnLeft();
            void addBoardBorder();
            void removeBoardBorder();
            void addTurnToken();
            void removeTurnToken();

            void redraw();

            sf::RenderWindow m_window;
            sf::Color m_backgroundColor;
            sf::Vector2u m_size;
            sf::Vector2f m_scale;
            float m_piecePickerToBoardGap;

            std::unique_ptr<Menu> m_menu;
            std::unique_ptr<WorkWindow> m_workWindow;
            std::unique_ptr<ToolWindow> m_toolWindow;
            std::unique_ptr<ToolPickerWindow> m_toolPickerWindow;

            std::map<sf::Mouse::Button, sigrid::Tool> m_tools;

            std::map<sf::Mouse::Button, bool> m_isMouseButtonPressedMap;
            std::map<sf::Mouse::Button, sf::Vector2f> m_mouseButtonPressedPositionMap;

            std::unique_ptr<FontManager> m_fontManagerPtr;
            std::unique_ptr<ColorManager> m_tileColorManagerPtr;
            std::unique_ptr<ColorManager> m_arrowColorManagerPtr;
            std::unique_ptr<ToolManager> m_toolManagerPtr;
            std::unique_ptr<PieceManager> m_pieceManagerPtr;
    };
}