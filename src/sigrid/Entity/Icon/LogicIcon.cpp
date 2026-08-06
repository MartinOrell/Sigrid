#include "sigrid/Entity/Icon/LogicIcon.h"

void sigrid::LogicIcon::setFilename(const sigrid::String& filename){
    m_filename = filename;
}

sigrid::IconDataContainer sigrid::LogicIcon::getContainer() const{

    sigrid::IconDataContainer container;
    container.imageFilename = m_filename;
    return container;
}

sigrid::String sigrid::LogicIcon::getFilename() const{
    return m_filename;
}

bool sigrid::LogicIcon::operator==(const sigrid::LogicIcon& rhs) const{
    return m_filename == rhs.m_filename;
}

bool sigrid::LogicIcon::operator!=(const sigrid::LogicIcon& rhs) const{
    return !(*this == rhs);
}