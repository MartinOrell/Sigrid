#include "Tool.h"

#include <iostream>

using namespace sigrid;

Tool::Tool(const ToolSelection& selection)
: m_selection(selection)
, m_arrowColorId(-1)
, m_circleColorId(-1){}

const ToolSelection Tool::selection() const{
    return m_selection;
}

LogicPiece Tool::getLogicPiece() const{
    return *m_logicPiece;
}

GraphicPiece Tool::getGraphicPiece() const{
    return *m_graphicPiece;
}

const int Tool::arrowColorId() const{
    return m_arrowColorId;
}

const int Tool::getCircleColorId() const{
    return m_circleColorId;
}

void Tool::setPiece(const LogicPiece& logicPiece, const GraphicPiece& graphicPiece){
    m_logicPiece = std::make_unique<LogicPiece>(logicPiece);
    m_graphicPiece = std::make_unique<GraphicPiece>(graphicPiece);
}

void Tool::setSelection(const ToolSelection& selection){
    m_selection = selection;
}

void Tool::setArrow(const int colorId){
    m_arrowColorId = colorId;
}

void Tool::setCircle(const int colorId){
    m_circleColorId = colorId;
}