#include "sigrid/Entity/Tile/LogicTile.h"

int sigrid::LogicTile::getColorId() const{
    return m_colorId;
}

std::optional<int> sigrid::LogicTile::getHighlightColorId() const{

    if(!m_isHighlightVisible){
        return std::nullopt;
    }
    return m_highlightColorId;
}

void sigrid::LogicTile::setColor(const int colorId){
    m_colorId = colorId;
}

void sigrid::LogicTile::setHighlightColor(const int colorId){

    m_highlightColorId = colorId;
    m_isHighlightVisible = true;
}

void sigrid::LogicTile::removeHighlight(){
    m_isHighlightVisible = false;
}

bool sigrid::LogicTile::operator<(const LogicTile& rhs) const{
    return m_colorId < rhs.m_colorId;
}

bool sigrid::LogicTile::operator==(const LogicTile& rhs) const{
    return m_colorId == rhs.m_colorId;
}

bool sigrid::LogicTile::operator!=(const LogicTile& rhs) const{
    return !(*this == rhs);
}