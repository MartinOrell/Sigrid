#pragma once

#include <map>
#include <SFML/Window/Mouse.hpp>
#include "../Tool/Tool.h"

namespace sigrid{

    class InputHandler{

        public:
            InputHandler();

            void addTool(const sf::Mouse::Button& button, sigrid::Tool tool);

            void setEntity(const sf::Mouse::Button& button, const sigrid::LogicEntity& logicEntity);

            void setArrow(const sf::Mouse::Button& button, const int& colorId);

            void setSelection(const sf::Mouse::Button& button, const ToolSelection& selection);

            sigrid::Tool* getToolPtr(const sf::Mouse::Button& button);

        private:

            std::map<sf::Mouse::Button, sigrid::Tool> m_tools;

    };

}