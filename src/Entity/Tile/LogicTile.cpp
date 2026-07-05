#include "LogicTile.h"

using namespace sigrid;

LogicTile::LogicTile(){}

LogicTile::LogicTile(const int colorId)
: m_colorId(colorId){}

int LogicTile::getColorId() const{
    return m_colorId;
}

std::optional<int> LogicTile::getHighlightColorId() const{

    if(!m_isHighlightVisible){
        return std::nullopt;
    }
    return m_highlightColorId;
}

void LogicTile::setColor(const int colorId){
    m_colorId = colorId;
}

void LogicTile::setHighlightColor(const int colorId){

    m_highlightColorId = colorId;
    m_isHighlightVisible = true;
}

void LogicTile::removeHighlight(){
    m_isHighlightVisible = false;
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