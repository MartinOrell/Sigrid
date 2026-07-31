#pragma once

#include <string>

namespace sigrid{

class LogicIcon{

  public:

    LogicIcon() = default;
    LogicIcon(const LogicIcon&) = default;
    LogicIcon(LogicIcon&&) = default;
    LogicIcon& operator=(const LogicIcon&) = default;
    LogicIcon& operator=(LogicIcon&&) = default;

    void setFilename(const std::string& name);
    std::string getFilename() const;

    bool operator==(const LogicIcon& rhs) const;
    bool operator!=(const LogicIcon& rhs) const;

  private:

    std::string m_filename;
};

}  // namespace sigrid