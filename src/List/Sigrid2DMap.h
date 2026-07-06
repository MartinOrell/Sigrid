#pragma once

#include <map>
#include <optional>
#include <functional> //Reference wrapper

#include "List/SigridVector.h"
#include "Coord/Coord.h"

namespace sigrid{

    template <typename T> class Sigrid2DMap{

        public:
            Sigrid2DMap();
            
            void setInsertPattern(const SigridVector<T>& insertPattern);
            void setNumColumns(const unsigned int& columns);
            void setNumRows(const unsigned int& rows);
            void setSize(const unsigned int& columns, const unsigned int& rows);

            bool addColumnLeft();
            bool addColumnRight();
            bool addRowUp();
            bool addRowDown();
            bool removeLeftColumn();
            bool removeRightColumn();
            bool removeTopRow();
            bool removeBottomRow();

            void clear();

            std::optional<std::reference_wrapper<T>> at(const Coord& coord);
            const std::optional<std::reference_wrapper<const T>> at(const Coord& coord) const;

            bool removeAt(const Coord& coord);

            const unsigned int& numColumns() const;
            const unsigned int& numRows() const;
            const SigridVector<T>& getInsertPattern() const;

        private:

            T getInsertElement(const Coord& coord) const;

            void refill();

            void shiftInsertPatternRight();

        unsigned int m_columns = 0;
        unsigned int m_rows = 0;
        std::map<Coord, T> m_map;
        SigridVector<T> m_insertPattern;
    };
}