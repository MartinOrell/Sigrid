#include "LogicTile.h"

using namespace sigrid;

LogicTile::LogicTile(const int colorId)
: m_colorId(colorId){}

int LogicTile::getColorId() const{
    return m_colorId;
}

void LogicTile::setColor(const int colorId){
    m_colorId = colorId;
}

bool LogicTile::operator<(const LogicTile& rhs) const{
    return m_colorId < rhs.m_colorId;
}

bool LogicTile::operator==(const LogicTile& rhs) const{
    return m_colorId == rhs.m_colorId;
}

bool LogicTile::operator!=(const LogicTile& rhs) const{
    return !(*this == rhs);
}