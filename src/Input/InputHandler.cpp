#include "InputHandler.h"

using namespace sigrid;

InputHandler::InputHandler(){}

void InputHandler::addTool(const sf::Mouse::Button& button, sigrid::Tool tool){
    m_tools.insert({button,std::move(tool)});
}

void InputHandler::addTool(const sf::Keyboard::Key& button, sigrid::Action action){
    m_keyboardActions.insert({button, std::move(action)});
}

void InputHandler::addCtrlTool(const sf::Keyboard::Key& button, sigrid::Action action){
    m_ctrlKeyboardActions.insert({button, std::move(action)});
}

void InputHandler::addCtrlShiftTool(const sf::Keyboard::Key& button, sigrid::Action action){
    m_ctrlShiftKeyboardActions.insert({button, std::move(action)});
}

void InputHandler::setEntity(const sf::Mouse::Button& button, const sigrid::LogicEntity& logicEntity){
    m_tools.at(button).setEntity(logicEntity);
}

void InputHandler::setArrow(const sf::Mouse::Button& button, const int& colorId){
    m_tools.at(button).setArrow(colorId);
}

void InputHandler::setSelection(const sf::Mouse::Button& button, const ToolSelection& selection){
    m_tools.at(button).setSelection(selection);
}

sigrid::Tool* InputHandler::getToolPtr(const sf::Mouse::Button& button){
    return &m_tools.at(button);
}

std::optional<sigrid::Action> InputHandler::getAction(const sf::Keyboard::Key& key){
    auto it = m_keyboardActions.find(key);
    if(it == m_keyboardActions.end()){
        return std::nullopt;
    }
    
    return it->second;
}

std::optional<sigrid::Action> InputHandler::getCtrlAction(const sf::Keyboard::Key& key){
    auto it = m_ctrlKeyboardActions.find(key);
    if(it == m_ctrlKeyboardActions.end()){
        return std::nullopt;
    }
    
    return it->second;
}

std::optional<sigrid::Action> InputHandler::getCtrlShiftAction(const sf::Keyboard::Key& key){
    auto it = m_ctrlShiftKeyboardActions.find(key);
    if(it == m_ctrlShiftKeyboardActions.end()){
        return std::nullopt;
    }
    
    return it->second;
}