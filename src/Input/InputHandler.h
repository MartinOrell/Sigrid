#pragma once

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "List/Map.h"
#include "Tool/Tool.h"
#include "Action/Action.h"

namespace sigrid{

class InputHandler{

  public:

    InputHandler() = default;
    InputHandler(const InputHandler&) = default;
    InputHandler(InputHandler&&) = default;
    InputHandler& operator=(const InputHandler&) = default;
    InputHandler& operator=(InputHandler&&) = default;

    void addTool(const sf::Mouse::Button& button, sigrid::Tool tool);

    void addTool(const sf::Keyboard::Key& button, sigrid_action::Action action);

    void addCtrlTool(const sf::Keyboard::Key& button, sigrid_action::Action action);

    void addCtrlShiftTool(const sf::Keyboard::Key& button, sigrid_action::Action action);

    void setEntity(const sf::Mouse::Button& button, const sigrid::LogicEntity& logicEntity);

    void setArrow(const sf::Mouse::Button& button, const int& colorId);

    void setSelection(const sf::Mouse::Button& button, const ToolSelection& selection);

    std::optional<sigrid::Tool*> getToolPtr(const sf::Mouse::Button& button);

    std::optional<sigrid_action::Action> getAction(const sf::Keyboard::Key& key);

    std::optional<sigrid_action::Action> getCtrlAction(const sf::Keyboard::Key& key);

    std::optional<sigrid_action::Action> getCtrlShiftAction(const sf::Keyboard::Key& key);

  private:

    sigrid_list::Map<sf::Mouse::Button, sigrid::Tool> m_tools;
    sigrid_list::Map<sf::Keyboard::Key, sigrid_action::Action> m_keyboardActions;
    sigrid_list::Map<sf::Keyboard::Key, sigrid_action::Action> m_ctrlKeyboardActions;
    sigrid_list::Map<sf::Keyboard::Key, sigrid_action::Action> m_ctrlShiftKeyboardActions;

};

}  // namespace sigrid