#include "Tool.h"

#include <iostream>

using namespace sigrid;

Tool::Tool(const ToolSelection& selection)
: m_selection(selection)
, m_arrowColorId(-1){}

const ToolSelection Tool::selection() const{
    return m_selection;
}

LogicEntity Tool::getEntity() const{
    return *m_entity;
}

const int Tool::arrowColorId() const{
    return m_arrowColorId;
}

void Tool::setEntity(const LogicEntity& entity){
    m_entity = std::make_unique<LogicEntity>(entity);
}

void Tool::setSelection(const ToolSelection& selection){
    m_selection = selection;
}

void Tool::setArrow(const int colorId){
    m_arrowColorId = colorId;
}