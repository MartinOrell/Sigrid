#include "LogicArrow.h"

using namespace sigrid;

LogicArrow::LogicArrow(const Coord& fromCoord, const Coord& toCoord, const int colorId)
: m_fromCoord(fromCoord)
, m_toCoord(toCoord)
, m_colorId(colorId){}

Coord LogicArrow::fromCoord() const{
    return m_fromCoord;
}

Coord LogicArrow::toCoord() const{
    return m_toCoord;
}

int LogicArrow::colorId() const{
    return m_colorId;
}

void LogicArrow::set(const Coord& fromCoord, const Coord& toCoord){
    m_fromCoord = fromCoord;
    m_toCoord = toCoord;
}

void LogicArrow::setColor(const int colorId){
    m_colorId = colorId;
}

bool LogicArrow::operator<(const LogicArrow& rhs) const{
    if(m_fromCoord < rhs.m_fromCoord){
        return true;
    }
    if(rhs.m_fromCoord < m_fromCoord){
        return false;
    }
    if(m_toCoord < rhs.m_toCoord){
        return true;
    }
    if(rhs.m_toCoord < m_toCoord){
        return false;
    }
    return m_colorId < rhs.m_colorId;
}

bool LogicArrow::operator==(const LogicArrow& rhs) const{
    return(
        m_fromCoord == rhs.m_fromCoord &&
        m_toCoord == rhs.m_toCoord &&
        m_colorId == rhs.m_colorId
    );
}

bool LogicArrow::operator!=(const LogicArrow& rhs) const{
    return !(*this == rhs);
}