#pragma once

#include "sigrid/Entity/Shape/Circle/CircleDataContainer.h"

namespace sigrid{

class LogicCircle{

  public:

    LogicCircle() = default;
    LogicCircle(const LogicCircle&) = default;
    LogicCircle(LogicCircle&&) = default;
    LogicCircle& operator=(const LogicCircle&) = default;
    LogicCircle& operator=(LogicCircle&&) = default;

    void setColor(const int colorId);

    int getColorId() const;
    CircleDataContainer getContainer() const;

    bool operator<(const LogicCircle& rhs) const;
    bool operator==(const LogicCircle& rhs) const;
    bool operator!=(const LogicCircle& rhs) const;

  private:

    int m_colorId = -1;
};

}  // namespace sigrid