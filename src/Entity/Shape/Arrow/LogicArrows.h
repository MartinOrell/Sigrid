#pragma once

#include <map>
#include <optional>

#include "../../../Coord/CoordPair.h"
#include "LogicArrow.h"

namespace sigrid{
    class LogicArrows{

        public:
            LogicArrows();

            void addArrow(const CoordPair& coordPair, const LogicArrow& arrow);
            void removeArrow(const CoordPair& coordPair);
            
            std::optional<LogicArrow> getArrow(const CoordPair& coordPair) const;

            void clear();
        private:
            std::map<CoordPair, LogicArrow> m_arrows;
    };
}
