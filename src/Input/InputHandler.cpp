#include "Input/InputHandler.h"

using namespace sigrid;

InputHandler::InputHandler(){}

void InputHandler::addTool(const sf::Mouse::Button& button, sigrid::Tool tool){
    m_tools.insert(button,std::move(tool));
}

void InputHandler::addTool(const sf::Keyboard::Key& button, sigrid_action::Action action){
    m_keyboardActions.insert(button, std::move(action));
}

void InputHandler::addCtrlTool(const sf::Keyboard::Key& button, sigrid_action::Action action){
    m_ctrlKeyboardActions.insert(button, std::move(action));
}

void InputHandler::addCtrlShiftTool(const sf::Keyboard::Key& button, sigrid_action::Action action){
    m_ctrlShiftKeyboardActions.insert(button, std::move(action));
}

void InputHandler::setEntity(const sf::Mouse::Button& button, const sigrid::LogicEntity& logicEntity){

    auto tool_o = m_tools.at(button);
    if(tool_o == std::nullopt){
        return;
    }
    auto& tool = tool_o.value().get();

    tool.setEntity(logicEntity);
}

void InputHandler::setArrow(const sf::Mouse::Button& button, const int& colorId){

    auto tool_o = m_tools.at(button);
    if(tool_o == std::nullopt){
        return;
    }
    auto& tool = tool_o.value().get();

    tool.setArrow(colorId);
}

void InputHandler::setSelection(const sf::Mouse::Button& button, const ToolSelection& selection){
    
    auto tool_o = m_tools.at(button);
    if(tool_o == std::nullopt){
        return;
    }
    auto& tool = tool_o.value().get();
    
    tool.setSelection(selection);
}

std::optional<sigrid::Tool*> InputHandler::getToolPtr(const sf::Mouse::Button& button){

    auto tool_o = m_tools.at(button);
    if(tool_o == std::nullopt){
        return std::nullopt;
    }
    return &(tool_o.value().get());
}

std::optional<sigrid_action::Action> InputHandler::getAction(const sf::Keyboard::Key& key){
    return m_keyboardActions.at(key);
}

std::optional<sigrid_action::Action> InputHandler::getCtrlAction(const sf::Keyboard::Key& key){
    return m_ctrlKeyboardActions.at(key);
}

std::optional<sigrid_action::Action> InputHandler::getCtrlShiftAction(const sf::Keyboard::Key& key){
    return m_ctrlShiftKeyboardActions.at(key);}