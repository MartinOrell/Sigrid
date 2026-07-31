#pragma once

#include <optional>

namespace sigrid{

class LogicTile{

  public:

    LogicTile() = default;
    LogicTile(const LogicTile&) = default;
    LogicTile(LogicTile&&) = default;
    LogicTile& operator=(const LogicTile&) = default;
    LogicTile& operator=(LogicTile&&) = default;

    int getColorId() const;
    std::optional<int> getHighlightColorId() const;

    void setColor(const int colorId);
    void setHighlightColor(const int colorId);

    void removeHighlight();

    bool operator<(const LogicTile& rhs) const;
    bool operator==(const LogicTile& rhs) const;
    bool operator!=(const LogicTile& rhs) const;

  private:

    int m_colorId = 0;
    bool m_isHighlightVisible = false;
    int m_highlightColorId;
};

}  // namespace sigrid