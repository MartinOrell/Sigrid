#pragma once

#include <iostream>

#include "sigrid/utilities/lists/Vector.h"

namespace sigrid{

template <typename T>
class ListSaver{

  public:

    ListSaver() = delete;
    ListSaver(const ListSaver&) = delete;
    ListSaver(ListSaver&&) = delete;
    ListSaver& operator=(const ListSaver&) = delete;
    ListSaver& operator=(ListSaver&&) = delete;

    ListSaver(const sigrid_list::Vector<T>, const int& indentLevel);
    ListSaver& operator=(const sigrid_list::Vector<T>);

    friend std::ostream& operator<<(std::ostream& out, const ListSaver& listSaver);

  private:

    sigrid_list::Vector<T> m_containers;
    int m_indentLevel;

};

}  // namespace sigrid