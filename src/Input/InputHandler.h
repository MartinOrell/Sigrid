#pragma once

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "List/Map.h"
#include "Tool/Tool.h"
#include "Action/Action.h"

namespace sigrid{

    class InputHandler{

        public:
            InputHandler();

            void addTool(const sf::Mouse::Button& button, sigrid::Tool tool);

            void addTool(const sf::Keyboard::Key& button, sigrid::Action action);

            void addCtrlTool(const sf::Keyboard::Key& button, sigrid::Action action);

            void addCtrlShiftTool(const sf::Keyboard::Key& button, sigrid::Action action);

            void setEntity(const sf::Mouse::Button& button, const sigrid::LogicEntity& logicEntity);

            void setArrow(const sf::Mouse::Button& button, const int& colorId);

            void setSelection(const sf::Mouse::Button& button, const ToolSelection& selection);

            std::optional<sigrid::Tool*> getToolPtr(const sf::Mouse::Button& button);

            std::optional<sigrid::Action> getAction(const sf::Keyboard::Key& key);

            std::optional<sigrid::Action> getCtrlAction(const sf::Keyboard::Key& key);

            std::optional<sigrid::Action> getCtrlShiftAction(const sf::Keyboard::Key& key);

        private:

            list::Map<sf::Mouse::Button, sigrid::Tool> m_tools;
            list::Map<sf::Keyboard::Key, sigrid::Action> m_keyboardActions;
            list::Map<sf::Keyboard::Key, sigrid::Action> m_ctrlKeyboardActions;
            list::Map<sf::Keyboard::Key, sigrid::Action> m_ctrlShiftKeyboardActions;

    };

}