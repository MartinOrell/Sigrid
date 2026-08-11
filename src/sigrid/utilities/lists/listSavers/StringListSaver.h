#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"

namespace sigrid{

class StringListSaver{

  public:
    StringListSaver() = delete;
    StringListSaver(const StringListSaver&) = delete;
    StringListSaver(StringListSaver&&) = delete;
    StringListSaver& operator=(const StringListSaver&) = delete;
    StringListSaver& operator=(StringListSaver&&) = delete;

    StringListSaver(const sigrid_list::Vector<sigrid::String>&);
    StringListSaver& operator=(const sigrid_list::Vector<sigrid::String>&);

    sigrid::String getMultiLineString(const int& indentLevel) const;

  private:

    sigrid_list::Vector<String> m_containers;

};

}  // namespace sigrid