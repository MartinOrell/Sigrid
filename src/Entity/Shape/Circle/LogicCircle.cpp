#include "Entity/Shape/Circle/LogicCircle.h"

using namespace sigrid;

LogicCircle::LogicCircle(){}

int LogicCircle::getColorId() const{
    return m_colorId;
}

void LogicCircle::setColor(const int colorId){
    m_colorId = colorId;
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