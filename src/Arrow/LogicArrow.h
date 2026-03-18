#pragma once

#include "../Coord/Coord.h"

namespace sigrid{
    class LogicArrow{

        public:
            LogicArrow(const Coord& fromCoord, const Coord& toCoord, const int colorId);
            int colorId() const;

            void setColor(const int colorId);

            bool operator<(const LogicArrow& rhs) const;
            bool operator==(const LogicArrow& rhs) const;
            bool operator!=(const LogicArrow& rhs) const;

        private:
            int m_colorId;
    };
}