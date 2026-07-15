#pragma once

#include <optional>
#include <functional> //Reference wrapper

#include "List/Map.h"
#include "List/Vector.h"
#include "Coord/Coord.h"

namespace sigrid_list{

    template <typename T> class AutoInsertMappedGrid{

        public:
            AutoInsertMappedGrid() = default;
            AutoInsertMappedGrid(const AutoInsertMappedGrid&) = default;
            AutoInsertMappedGrid(AutoInsertMappedGrid&&) = default;
            AutoInsertMappedGrid& operator=(const AutoInsertMappedGrid&) = default;
            AutoInsertMappedGrid& operator=(AutoInsertMappedGrid&&) = default;
            
            void setInsertPattern(const Vector<T>& insertPattern);
            void setNumColumns(const int& columns);
            void setNumRows(const int& rows);
            void setSize(const int& columns, const int& rows);

            bool addColumnLeft();
            bool addColumnRight();
            bool addRowUp();
            bool addRowDown();
            bool removeLeftColumn();
            bool removeRightColumn();
            bool removeTopRow();
            bool removeBottomRow();

            void clear();

            std::optional<std::reference_wrapper<T>> at(const sigrid::Coord& coord);
            const std::optional<std::reference_wrapper<const T>> at(const sigrid::Coord& coord) const;

            bool removeAt(const sigrid::Coord& coord);

            const int& numColumns() const;
            const int& numRows() const;
            const Vector<T>& getInsertPattern() const;

        private:

            T getInsertElement(const sigrid::Coord& coord) const;

            void refill();

            void shiftInsertPatternRight();

        int m_columns = 0;
        int m_rows = 0;
        Map<sigrid::Coord, T> m_map;
        Vector<T> m_insertPattern;
    };
}