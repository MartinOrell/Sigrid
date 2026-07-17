#pragma once

#include <string>

namespace sigrid{

class LogicPiece{

  public:

    LogicPiece();

    void setNotation(const std::string& notation);
    void setColorId(const int& colorId);

    int getColorId() const;
    std::string getNotation() const;

    bool operator==(const LogicPiece& rhs) const;
    bool operator!=(const LogicPiece& rhs) const;

  private:

    std::string m_notation = "";
    int m_colorId = -1;
};

}  // namespace sigrid