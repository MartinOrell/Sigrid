#include "sigrid/Entity/Shape/Circle/LogicCircle.h"

void sigrid::LogicCircle::setColor(const int colorId){
    m_colorId = colorId;
}

int sigrid::LogicCircle::getColorId() const{
    return m_colorId;
}

sigrid::CircleDataContainer sigrid::LogicCircle::getContainer() const{

    CircleDataContainer container;
    container.colorId = m_colorId;
    return container;
}

bool sigrid::LogicCircle::operator<(const sigrid::LogicCircle& rhs) const{
    return m_colorId < rhs.m_colorId;
}

bool sigrid::LogicCircle::operator==(const sigrid::LogicCircle& rhs) const{
    return m_colorId == rhs.m_colorId;
}

bool sigrid::LogicCircle::operator!=(const sigrid::LogicCircle& rhs) const{
    return !(*this == rhs);
}