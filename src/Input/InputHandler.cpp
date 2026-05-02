#include "InputHandler.h"

using namespace sigrid;

InputHandler::InputHandler(){
    m_keyboardActions.insert({sf::Keyboard::Key::Space, ActionType::SetTool{sf::Mouse::Button::Left, ToolSelection::Select}});
}

void InputHandler::addTool(const sf::Mouse::Button& button, sigrid::Tool tool){
    m_tools.insert({button,std::move(tool)});
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