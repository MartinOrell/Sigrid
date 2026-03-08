#include "LogicCircle.h"

using namespace sigrid;

LogicCircle::LogicCircle(const Coord& position, const int colorId)
: m_position(position)
, m_colorId(colorId){}

Coord LogicCircle::getPosition() const{
    return m_position;
}

int LogicCircle::getColorId() const{
    return m_colorId;
}

void LogicCircle::setPosition(const Coord& position){
    m_position = position;
}

void LogicCircle::setColor(const int colorId){
    m_colorId = colorId;
}

bool LogicCircle::operator<(const LogicCircle& rhs) const{
    if(m_position < rhs.m_position){
        return true;
    }
    return m_colorId < rhs.m_colorId;
}

bool LogicCircle::operator==(const LogicCircle& rhs) const{
    return m_position == rhs.m_position &&
        m_colorId == rhs.m_colorId;
}

bool LogicCircle::operator!=(const LogicCircle& rhs) const{
    return !(*this == rhs);
}