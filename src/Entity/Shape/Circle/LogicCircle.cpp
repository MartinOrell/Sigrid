#include "Entity/Shape/Circle/LogicCircle.h"

using namespace sigrid;

void LogicCircle::setColor(const int colorId){
    m_colorId = colorId;
}

int LogicCircle::getColorId() const{
    return m_colorId;
}

bool LogicCircle::operator<(const LogicCircle& rhs) const{
    return m_colorId < rhs.m_colorId;
}

bool LogicCircle::operator==(const LogicCircle& rhs) const{
    return m_colorId == rhs.m_colorId;
}

bool LogicCircle::operator!=(const LogicCircle& rhs) const{
    return !(*this == rhs);
}