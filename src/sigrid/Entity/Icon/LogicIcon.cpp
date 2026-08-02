#include "sigrid/Entity/Icon/LogicIcon.h"

using namespace sigrid;

void LogicIcon::setFilename(const sigrid::String& filename){
    m_filename = filename;
}

sigrid::String LogicIcon::getFilename() const{
    return m_filename;
}

bool LogicIcon::operator==(const LogicIcon& rhs) const{
    return m_filename == rhs.m_filename;
}

bool LogicIcon::operator!=(const LogicIcon& rhs) const{
    return !(*this == rhs);
}