#pragma once

namespace sigrid{
    class LogicCircle{

        public:
            LogicCircle(const int colorId);
            int getColorId() const;

            void setColor(const int colorId);

            bool operator<(const LogicCircle& rhs) const;
            bool operator==(const LogicCircle& rhs) const;
            bool operator!=(const LogicCircle& rhs) const;

        private:
            int m_colorId;
    };
}