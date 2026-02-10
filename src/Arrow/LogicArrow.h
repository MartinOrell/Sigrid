#pragma once

#include "../Board/Coord.h"

namespace sigrid{
    class LogicArrow{

        public:
            LogicArrow(const Coord& fromCoord, const Coord& toCoord, const int colorId);
            Coord fromCoord() const;
            Coord toCoord() const;
            int colorId() const;

            void set(const Coord& fromCoord, const Coord& toCoord);
            void setColor(const int colorId);

            bool operator<(const LogicArrow& rhs) const;
            bool operator==(const LogicArrow& rhs) const;
            bool operator!=(const LogicArrow& rhs) const;

        private:
            Coord m_fromCoord;
            Coord m_toCoord;
            int m_colorId;
    };
}