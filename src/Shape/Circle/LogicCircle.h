#pragma once

#include "../../Coord/Coord.h"

namespace sigrid{
    class LogicCircle{

        public:
            LogicCircle(const Coord& coord, const int colorId);
            Coord getPosition() const;
            int getColorId() const;

            void setPosition(const Coord& coord);
            void setColor(const int colorId);

            bool operator<(const LogicCircle& rhs) const;
            bool operator==(const LogicCircle& rhs) const;
            bool operator!=(const LogicCircle& rhs) const;

        private:
            Coord m_position;
            int m_colorId;
    };
}