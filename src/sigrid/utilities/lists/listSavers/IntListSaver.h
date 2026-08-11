#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"

namespace sigrid{

class IntListSaver{

  public:
    IntListSaver() = delete;
    IntListSaver(const IntListSaver&) = delete;
    IntListSaver(IntListSaver&&) = delete;
    IntListSaver& operator=(const IntListSaver&) = delete;
    IntListSaver& operator=(IntListSaver&&) = delete;

    IntListSaver(const sigrid_list::Vector<int>&);
    IntListSaver& operator=(const sigrid_list::Vector<int>&);

    sigrid::String getMultiLineString(const int& indentLevel) const;

  private:

    sigrid_list::Vector<int> m_containers;

};

}  // namespace sigrid