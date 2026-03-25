#pragma once

namespace sigrid{
    class LogicTile{

        public:
            LogicTile(const int colorId);
            int getColorId() const;

            void setColor(const int colorId);

            bool operator<(const LogicTile& rhs) const;
            bool operator==(const LogicTile& rhs) const;
            bool operator!=(const LogicTile& rhs) const;

        private:
            int m_colorId;
    };
}