#pragma once

#include "sigrid/Entity/Shape/Arrow/ArrowDataContainer.h"

namespace sigrid{

class LogicArrow{

  public:

    LogicArrow() = default;
    LogicArrow(const LogicArrow&) = default;
    LogicArrow(LogicArrow&&) = default;
    LogicArrow& operator=(const LogicArrow&) = default;
    LogicArrow& operator=(LogicArrow&&) = default;

    void setColor(const int colorId);

    int getColorId() const;
    ArrowDataContainer getContainer() const;

    bool operator<(const LogicArrow& rhs) const;
    bool operator==(const LogicArrow& rhs) const;
    bool operator!=(const LogicArrow& rhs) const;

  private:

    int m_colorId = -1;
};

}  // namespace sigrid