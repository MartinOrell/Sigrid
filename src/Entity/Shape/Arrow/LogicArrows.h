#pragma once

#include <optional>

#include "List/OrderedMap.h"
#include "Coord/CoordPair.h"
#include "Entity/Shape/Arrow/LogicArrow.h"

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
            list::OrderedMap<CoordPair, LogicArrow> m_arrows;
    };
}
