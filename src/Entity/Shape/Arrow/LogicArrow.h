#pragma once

namespace sigrid{

class LogicArrow{

  public:

    LogicArrow();

    void setColor(const int colorId);

    int getColorId() const;

    bool operator<(const LogicArrow& rhs) const;
    bool operator==(const LogicArrow& rhs) const;
    bool operator!=(const LogicArrow& rhs) const;

  private:

    int m_colorId = -1;
};

}  // namespace sigrid