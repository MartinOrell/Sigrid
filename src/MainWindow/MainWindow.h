#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <memory>

#include "../Menu/Menu.h"
#include "../WorkWindow/WorkWindow.h"
#include "../ToolWindow/ToolWindow.h"
#include "../ToolPicker/ToolPickerWindow.h"

#include "../Tool/Tool.h"

namespace sigrid{
    class MainWindow{
        public:
            MainWindow(sf::Vector2u size, std::string windowName);
            void add(std::unique_ptr<sigrid::Menu> menu);
            void add(std::unique_ptr<sigrid::WorkWindow> workWindow);
            void add(std::unique_ptr<sigrid::ToolWindow> toolWindow);
            void add(std::unique_ptr<sigrid::ToolPickerWindow> toolPickerWindow);
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
            void pickPiece(const sigrid::Piece& piece);
            void pickPieceColor(const sigrid::Piece& piece);
            void pickArrow(const int colorId);
            void pickArrowColor(const int colorId);
            void setTool(const sigrid::ToolSelection& selection, const sf::Mouse::Button& button);
            void showColorTools();
            void hideColorTools();
            void showTools();
            void hideTools();
            void saveLogicBoard();
            void saveBoardImage(const std::string& imageFilename);
            void addCoordinates();
            void removeCoordinates();
            void moveCoordinatesOutside();
            void moveCoordinatesInside();
            void setBigCoordinates();
            void setSmallCoordinates();
            void addBoardBorder();
            void removeBoardBorder();
            void addPlayerToMoveToken();
            void removePlayerToMoveToken();

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
            std::map<sf::Mouse::Button, sf::Vector2i> m_mouseButtonPressedPositionMap;
    };
}