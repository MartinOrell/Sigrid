#include "LogicArrow.h"

using namespace sigrid;

LogicArrow::LogicArrow(const Coord& fromCoord, const Coord& toCoord, const int colorId)
: m_colorId(colorId){}

int LogicArrow::colorId() const{
    return m_colorId;
}

void LogicArrow::setColor(const int colorId){
    m_colorId = colorId;
}

bool LogicArrow::operator<(const LogicArrow& rhs) const{
    return m_colorId < rhs.m_colorId;
}

bool LogicArrow::operator==(const LogicArrow& rhs) const{
    return m_colorId == rhs.m_colorId;
}

bool LogicArrow::operator!=(const LogicArrow& rhs) const{
    return !(*this == rhs);
}