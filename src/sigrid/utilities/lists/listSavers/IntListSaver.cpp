#include "sigrid/utilities/lists/listSavers/IntListSaver.h"

#include "sigrid/utilities/lists/Vector.h"

sigrid::IntListSaver::IntListSaver(const sigrid_list::Vector<int>& src){
    m_containers = src;
}

sigrid::IntListSaver& sigrid::IntListSaver::operator=(const sigrid_list::Vector<int>& rhs){

    m_containers = rhs;
    return *this;
}

sigrid::String sigrid::IntListSaver::getMultiLineString(const int& indentLevel) const{

    sigrid::String out;

    sigrid::String indent0;
    for(int i = 0; i < indentLevel; ++i){
        indent0.append("  ");
    }
    sigrid::String indent1 = indent0;
    indent1.append("  ");

    out.append("[");
    for(const auto& container: m_containers){

        sigrid::String containerString;
        containerString.set(std::to_string(container));

        out.append("\n");
        out.append(indent1);
        out.append(containerString);
    }
    out.append("\n");
    out.append(indent0);
    out.append("]");

    return out;
}