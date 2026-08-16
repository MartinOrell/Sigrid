#include "sigrid/Tool/Tool.h"

#include <iostream>

#include "sigrid/utilities/String/String.h"
#include "sigrid/Tool/ToolContainer.h"

using namespace sigrid;

std::optional<sigrid::ToolSelection> getToolSelection(const sigrid::String& toolname){
    
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
        return std::nullopt;
    }
}

bool sigrid::Tool::load(const ToolContainer& data){
    
    const auto selection_o = getToolSelection(data.selection);
    if(selection_o == std::nullopt){
        std::cerr << "Tool: Unknown tool name: \"" << data.selection << "\"."
            << " Failed to load Tool" << std::endl;
        return false;
    }
    else{
        m_selection = selection_o.value();
    }

    m_arrowColorId = data.colorId;

    return true;
}

std::optional<ToolContainer> Tool::getContainer() const{

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
            return std::nullopt;
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