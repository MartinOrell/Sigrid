#pragma once

#include "sigrid/utilities/String/String.h"

namespace sigrid{

class LogicIcon{

  public:

    LogicIcon() = default;
    LogicIcon(const LogicIcon&) = default;
    LogicIcon(LogicIcon&&) = default;
    LogicIcon& operator=(const LogicIcon&) = default;
    LogicIcon& operator=(LogicIcon&&) = default;

    void setFilename(const sigrid::String& name);
    sigrid::String getFilename() const;

    bool operator==(const LogicIcon& rhs) const;
    bool operator!=(const LogicIcon& rhs) const;

  private:

    sigrid::String m_filename;
};

}  // namespace sigrid