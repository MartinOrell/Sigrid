#include "LogicTile.h"

using namespace sigrid;

LogicTile::LogicTile(){}

LogicTile::LogicTile(const int colorId)
: m_colorId(colorId){}

LogicTile::LogicTile(const LogicTile& src){
    m_colorId = src.m_colorId;
    m_isHighlightVisible = src.m_isHighlightVisible;
    m_highlightColorId = src.m_highlightColorId;
}

LogicTile& LogicTile::operator =(const LogicTile& rhs){
    m_colorId = rhs.m_colorId;
    m_isHighlightVisible = rhs.m_isHighlightVisible;
    m_highlightColorId = rhs.m_highlightColorId;
    return *this;
}

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