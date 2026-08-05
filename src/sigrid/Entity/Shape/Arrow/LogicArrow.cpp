#include "sigrid/Entity/Shape/Arrow/LogicArrow.h"

void sigrid::LogicArrow::setColor(const int colorId){
    m_colorId = colorId;
}

int sigrid::LogicArrow::getColorId() const{
    return m_colorId;
}

sigrid::ArrowDataContainer sigrid::LogicArrow::getContainer() const{

    sigrid::ArrowDataContainer container;
    container.colorId = m_colorId;
    return container;
}

bool sigrid::LogicArrow::operator<(const sigrid::LogicArrow& rhs) const{
    return m_colorId < rhs.m_colorId;
}

bool sigrid::LogicArrow::operator==(const sigrid::LogicArrow& rhs) const{
    return m_colorId == rhs.m_colorId;
}

bool sigrid::LogicArrow::operator!=(const sigrid::LogicArrow& rhs) const{
    return !(*this == rhs);
}