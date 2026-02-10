#include "Tool.h"

#include <iostream>

using namespace sigrid;

Tool::Tool(const ToolSelection selection)
: m_selection(selection)
, m_arrowColorId(0){}

const ToolSelection Tool::selection() const{
    return m_selection;
}

const Piece Tool::piece() const{
    return *m_piece;
}

const int Tool::arrowColorId() const{
    return m_arrowColorId;
}

void Tool::setPiece(const Piece& piece){
    m_piece = std::make_unique<Piece>(piece);
}

void Tool::setSelection(const ToolSelection selection){
    m_selection = selection;
}

void Tool::setArrow(const int colorId){
    m_arrowColorId = colorId;
}