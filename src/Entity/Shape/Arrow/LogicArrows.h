#pragma once

#include <optional>

#include "../../../List/SigridMap.h"
#include "../../../Coord/CoordPair.h"
#include "LogicArrow.h"

namespace sigrid{
    class LogicArrows{

        public:
            LogicArrows();

            void addArrow(const CoordPair& coordPair, const LogicArrow& arrow);
            void removeArrow(const CoordPair& coordPair);
            
            std::optional<LogicArrow> getArrow(const CoordPair& coordPair) const;

            void removeColumn(const int& columnId);
            void removeRow(const int& rowId);

            void moveArrowsRight();
            void moveArrowsLeft();
            void moveArrowsUp();
            void moveArrowsDown();

            void clear();
        private:
            SigridMap<CoordPair, LogicArrow> m_arrows;
    };
}
