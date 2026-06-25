#pragma once

#include <memory>
#include <optional>

namespace sigrid{
    class LogicTile{

        public:
            LogicTile();
            LogicTile(const int colorId);
            LogicTile(const LogicTile& src);
            LogicTile& operator =(const LogicTile& rhs);

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
            std::unique_ptr<int> m_highlightColorIdPtr;
    };
}