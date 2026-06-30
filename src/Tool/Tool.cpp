#include "Tool.h"

#include "ToolContainer.h"

#include <iostream>

using namespace sigrid;

sigrid::ToolSelection getTool(const std::string& toolname){
    if(toolname == "Select"){
        return sigrid::ToolSelection::Select;
    }
    else if(toolname == "DrawArrow"){
        return sigrid::ToolSelection::DrawArrow;
    }
    else if(toolname == "EntityPicker"){
        return sigrid::EntityPicker;
    }
    else{
        std::cerr << "Tool: Unknown tool name: " << toolname <<std::endl;
        return sigrid::ToolSelection::Select;
    }
}

Tool::Tool(){}

Tool::Tool(const Tool& src){
    *this = src;
}

Tool::Tool(const ToolContainer& data)
: m_selection(getTool(data.selection))
, m_arrowColorId(data.colorId){}

Tool& Tool::operator=(const Tool& rhs){
    m_selection = rhs.m_selection;
    m_arrowColorId = rhs.m_arrowColorId;
    
    if(rhs.m_entity){
        if(!m_entity){
            m_entity = std::make_unique<LogicEntity>(*(rhs.m_entity));
        }
        else{
            *m_entity = *(rhs.m_entity);
        }
    }

    return *this;
}

const ToolSelection Tool::selection() const{
    return m_selection;
}

LogicEntity Tool::getEntity() const{
    return *m_entity;
}

int Tool::getArrowColorId() const{
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