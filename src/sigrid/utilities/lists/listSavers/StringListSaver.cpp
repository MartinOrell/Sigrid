#include "sigrid/utilities/lists/listSavers/StringListSaver.h"

#include "sigrid/utilities/lists/Vector.h"

sigrid::StringListSaver::StringListSaver(const sigrid_list::Vector<sigrid::String>& src){
    m_containers = src;
}

sigrid::StringListSaver& sigrid::StringListSaver::operator=(const sigrid_list::Vector<sigrid::String>& rhs){

    m_containers = rhs;
    return *this;
}

sigrid::String sigrid::StringListSaver::getMultiLineString(const int& indentLevel) const{

    sigrid::String out;

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    out.append("[");
    for(const auto& container: m_containers){
        out.append("\n");
        out.append(indent1);
        out.append(container);
    }
    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}