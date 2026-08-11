#pragma once

#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/String/String.h"

namespace sigrid{

template <typename T>
class ListSaver{

  public:

    ListSaver() = delete;
    ListSaver(const ListSaver&) = delete;
    ListSaver(ListSaver&&) = delete;
    ListSaver& operator=(const ListSaver&) = delete;
    ListSaver& operator=(ListSaver&&) = delete;

    ListSaver(const sigrid_list::Vector<T>);
    ListSaver& operator=(const sigrid_list::Vector<T>);

    sigrid::String getMultiLineString(const int& indentLevel) const;

  private:

    sigrid_list::Vector<T> m_containers;

};

}  // namespace sigrid