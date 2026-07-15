#pragma once

#include <string>

namespace sigrid{

class LogicIcon{

  public:

    LogicIcon();
    void setFilename(const std::string& name);
    std::string getFilename() const;

    bool operator==(const LogicIcon& rhs) const;
    bool operator!=(const LogicIcon& rhs) const;

  private:

    std::string m_filename;
};

}  // namespace sigrid