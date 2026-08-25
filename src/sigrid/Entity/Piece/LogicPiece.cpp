#include "sigrid/Entity/Piece/LogicPiece.h"

#include <cctype>

void sigrid::LogicPiece::setNotation(const sigrid::String& notation){
    m_notation = notation;
}

void sigrid::LogicPiece::setColorId(const int& colorId){
    m_colorId = colorId;
}

sigrid::String sigrid::LogicPiece::getNotation() const{
    return m_notation;
}

sigrid::PieceDataContainer sigrid::LogicPiece::getContainer() const{
    
    sigrid::PieceDataContainer container;
    container.colorId = m_colorId;
    container.name = m_notation;
    return container;
}

int sigrid::LogicPiece::getColorId() const{
    return m_colorId;
}

bool sigrid::LogicPiece::operator==(const LogicPiece& rhs) const{

    if(m_colorId != rhs.m_colorId){
        return false;
    }

    if(m_notation.length() != rhs.m_notation.length()){
        return false;
    }

    return m_notation.getUpper() == rhs.m_notation.getUpper();
}

bool sigrid::LogicPiece::operator!=(const LogicPiece& rhs) const{
    return !(*this == rhs);
}