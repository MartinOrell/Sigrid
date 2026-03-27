#include "LogicTile.h"

using namespace sigrid;

LogicTile::LogicTile(const int colorId)
: m_colorId(colorId){}

LogicTile::LogicTile(const LogicTile& src){
    m_colorId = src.m_colorId;
    if(src.m_highlightColorIdPtr){
        m_highlightColorIdPtr = std::make_unique<int>(*(src.m_highlightColorIdPtr));
    }
}

LogicTile& LogicTile::operator =(const LogicTile& rhs){
    m_colorId = rhs.m_colorId;
    if(rhs.m_highlightColorIdPtr){
        m_highlightColorIdPtr = std::make_unique<int>(*(rhs.m_highlightColorIdPtr));
    }
    return *this;
}

int LogicTile::getColorId() const{
    return m_colorId;
}

std::optional<int> LogicTile::getHighlightColorId() const{
    if(!m_highlightColorIdPtr){
        return std::nullopt;
    }
    return *m_highlightColorIdPtr;
}

void LogicTile::setColor(const int colorId){
    m_colorId = colorId;
}

void LogicTile::setHighlightColor(const int colorId){
    if(m_highlightColorIdPtr){
        *m_highlightColorIdPtr = colorId;
    }
    else{
        m_highlightColorIdPtr = std::make_unique<int>(colorId);
    }
}

void LogicTile::removeHighlight(){
    m_highlightColorIdPtr.reset();
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