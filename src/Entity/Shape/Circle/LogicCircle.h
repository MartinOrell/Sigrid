#pragma once

namespace sigrid{

class LogicCircle{

  public:

    LogicCircle();

    void setColor(const int colorId);

    int getColorId() const;

    bool operator<(const LogicCircle& rhs) const;
    bool operator==(const LogicCircle& rhs) const;
    bool operator!=(const LogicCircle& rhs) const;

  private:

    int m_colorId = -1;
};

}  // namespace sigrid