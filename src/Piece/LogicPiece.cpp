#include "LogicPiece.h"
#include <iostream>
#include <cctype>

using namespace sigrid;

LogicPiece::LogicPiece(std::string notation, int colorId)
: m_notation(notation)
, m_colorId(colorId){}


std::string LogicPiece::notation() const{
    return m_notation;
}

int LogicPiece::colorId() const{
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