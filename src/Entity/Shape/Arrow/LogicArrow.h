#pragma once

namespace sigrid{

class LogicArrow{

  public:

    LogicArrow();
    int getColorId() const;

    void setColor(const int colorId);

    bool operator<(const LogicArrow& rhs) const;
    bool operator==(const LogicArrow& rhs) const;
    bool operator!=(const LogicArrow& rhs) const;

  private:

    int m_colorId = -1;
};

}  // namespace sigrid