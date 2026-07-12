#pragma once

#include <optional>
#include <functional> //Reference wrapper

#include "List/Map.h"
#include "List/Vector.h"
#include "Coord/Coord.h"

namespace sigrid{namespace list{

    template <typename T> class AutoInsertMappedGrid{

        public:
            AutoInsertMappedGrid() = default;
            AutoInsertMappedGrid(const AutoInsertMappedGrid&) = default;
            AutoInsertMappedGrid(AutoInsertMappedGrid&&) = default;
            AutoInsertMappedGrid& operator=(const AutoInsertMappedGrid&) = default;
            AutoInsertMappedGrid& operator=(AutoInsertMappedGrid&&) = default;
            
            void setInsertPattern(const Vector<T>& insertPattern);
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
            const Vector<T>& getInsertPattern() const;

        private:

            T getInsertElement(const Coord& coord) const;

            void refill();

            void shiftInsertPatternRight();

        unsigned int m_columns = 0;
        unsigned int m_rows = 0;
        Map<Coord, T> m_map;
        Vector<T> m_insertPattern;
    };
}}