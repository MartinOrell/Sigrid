#include "LogicIcon.h"

using namespace sigrid;

LogicIcon::LogicIcon(){}

void LogicIcon::setName(const std::string& name){
    m_name = name;
}

std::string LogicIcon::getName() const{
    return m_name;
}

bool LogicIcon::operator==(const LogicIcon& rhs) const{
    return m_name == rhs.m_name;
}

bool LogicIcon::operator!=(const LogicIcon& rhs) const{
    return !(*this == rhs);
}