#include "Entity/Shape/Arrow/LogicArrow.h"

using namespace sigrid;

LogicArrow::LogicArrow(){}

void LogicArrow::setColor(const int colorId){
    m_colorId = colorId;
}

int LogicArrow::getColorId() const{
    return m_colorId;
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