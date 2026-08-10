#include "sigrid/utilities/lists/listSavers/ListSaver.h"
#include "sigrid/utilities/lists/listSavers/ListSaver_contentTypes.h"

#include "sigrid/utilities/lists/Vector.h"

template<typename T>
sigrid::ListSaver<T>::ListSaver(const sigrid_list::Vector<T> src, const int& indentLevel){
    m_containers = src;
    m_indentLevel = indentLevel;
}

template<typename T>
sigrid::ListSaver<T>& sigrid::ListSaver<T>::operator=(const sigrid_list::Vector<T> rhs){

    m_containers = rhs;
    return *this;
}

sigrid::String getIndentSpace(const int& indentLevel){
    
    sigrid::String s;
    for(int i = 0; i < indentLevel; i++){
        s.append("  ");
    }
    return s;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::String>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n" << getIndentSpace(listSaver.m_indentLevel+1) << container;
    }
    out << "\n" << getIndentSpace(listSaver.m_indentLevel) << "]";

    return out;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::ColorContainer>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n  " << container;
    }
    out << "\n]";

    return out;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::PieceColor>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n" << getIndentSpace(listSaver.m_indentLevel+1) << container;
    }
    out << "\n" << getIndentSpace(listSaver.m_indentLevel) << "]";

    return out;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::PieceContainer>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n" << getIndentSpace(listSaver.m_indentLevel+1) << container;
    }
    out << "\n" << getIndentSpace(listSaver.m_indentLevel) << "]";

    return out;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::HeaderContainer>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n" << getIndentSpace(listSaver.m_indentLevel+1) << container;
    }
    out << "\n" << getIndentSpace(listSaver.m_indentLevel) << "]";

    return out;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::MenuItemContainer>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n" << getIndentSpace(listSaver.m_indentLevel+1) << container;
    }
    out << "\n" << getIndentSpace(listSaver.m_indentLevel) << "]";

    return out;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::ToolBlockContainer>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n" << getIndentSpace(listSaver.m_indentLevel+1) << container;
    }
    out << "\n" << getIndentSpace(listSaver.m_indentLevel) << "]";

    return out;
}