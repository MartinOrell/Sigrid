#include "Entity/Piece/LogicPiece.h"

#include <cctype>

using namespace sigrid;

void LogicPiece::setNotation(const std::string& notation){
    m_notation = notation;
}

void LogicPiece::setColorId(const int& colorId){
    m_colorId = colorId;
}

std::string LogicPiece::getNotation() const{
    return m_notation;
}

int LogicPiece::getColorId() const{
    return m_colorId;
}

bool LogicPiece::operator==(const LogicPiece& rhs) const{

    if(m_colorId != rhs.m_colorId){
        return false;
    }

    if(m_notation.length() != rhs.m_notation.length()){
        return false;
    }

    for(int i = 0; i < m_notation.length(); i++){
        if(std::toupper(m_notation[i]) != std::toupper(rhs.m_notation[i])){
            return false;
        }
    }

    return true;
}

bool LogicPiece::operator!=(const LogicPiece& rhs) const{
    return !(*this == rhs);
}