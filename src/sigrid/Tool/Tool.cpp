#include "sigrid/Tool/Tool.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"
#include "sigrid/Tool/ToolContainer.h"

using namespace sigrid;

sigrid::ToolSelection getTool(const sigrid::String& toolname){
    
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

Tool::Tool(const ToolContainer& data)
: m_selection(getTool(data.selection))
, m_arrowColorId(data.colorId){}

ToolContainer Tool::getContainer() const{

    ToolContainer container;

    switch(m_selection){
        case ToolSelection::Select:
            container.selection = "Select";
            break;
        case ToolSelection::DrawArrow:
            container.selection = "DrawArrow";
            break;
        case ToolSelection::EntityPicker:
            container.selection = "EntityPicker";
            break;
        default:
            std::cerr << "Tool: Unknown tool name with id " << m_selection << "."
                << " toolname set to unknown." << std::endl;
            container.selection = "unknown";
            break;
    }

    container.colorId = m_arrowColorId;

    return container;
}

const ToolSelection Tool::selection() const{
    return m_selection;
}

std::optional<LogicEntity> Tool::getEntity() const{
    return m_entity_o;
}

int Tool::getArrowColorId() const{
    return m_arrowColorId;
}

void Tool::setEntity(const LogicEntity& entity){
    m_entity_o = entity;
}

void Tool::setSelection(const ToolSelection& selection){
    m_selection = selection;
}

void Tool::setArrow(const int colorId){
    m_arrowColorId = colorId;
}