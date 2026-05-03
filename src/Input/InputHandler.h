#pragma once

#include <map>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "../Tool/Tool.h"
#include "../Action/Action.h"

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

            sigrid::Tool* getToolPtr(const sf::Mouse::Button& button);

            std::optional<sigrid::Action> getAction(const sf::Keyboard::Key& key);

            std::optional<sigrid::Action> getCtrlAction(const sf::Keyboard::Key& key);

            std::optional<sigrid::Action> getCtrlShiftAction(const sf::Keyboard::Key& key);

        private:

            std::map<sf::Mouse::Button, sigrid::Tool> m_tools;
            std::map<sf::Keyboard::Key, sigrid::Action> m_keyboardActions;
            std::map<sf::Keyboard::Key, sigrid::Action> m_ctrlKeyboardActions;
            std::map<sf::Keyboard::Key, sigrid::Action> m_ctrlShiftKeyboardActions;

    };

}