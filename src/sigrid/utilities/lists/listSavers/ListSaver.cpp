#include "sigrid/utilities/lists/listSavers/ListSaver.h"
#include "sigrid/utilities/lists/listSavers/ListSaver_contentTypes.h"

#include "sigrid/utilities/lists/Vector.h"

template<typename T>
sigrid::ListSaver<T>::ListSaver(const sigrid_list::Vector<T> src){
    m_containers = src;
}

template<typename T>
sigrid::ListSaver<T>& sigrid::ListSaver<T>::operator=(const sigrid_list::Vector<T> rhs){

    m_containers = rhs;
    return *this;
}

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::ListSaver<sigrid::ColorContainer>& listSaver){

    out << "[";
    for(const auto& container: listSaver.m_containers){
        out << "\n  " << container;
    }
    out << "\n]";

    return out;
}