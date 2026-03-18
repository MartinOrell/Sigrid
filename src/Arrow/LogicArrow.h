#pragma once

#include "../Coord/Coord.h"

namespace sigrid{
    class LogicArrow{

        public:
            LogicArrow(const int colorId);
            int getColorId() const;

            void setColor(const int colorId);

            bool operator<(const LogicArrow& rhs) const;
            bool operator==(const LogicArrow& rhs) const;
            bool operator!=(const LogicArrow& rhs) const;

        private:
            int m_colorId;
    };
}