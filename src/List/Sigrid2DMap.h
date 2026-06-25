#pragma once

#include <map>
#include <vector>
#include <optional>
#include <functional> //Reference wrapper

#include "../Coord/Coord.h"

namespace sigrid{

    template <typename T> class Sigrid2DMap{

        public:
            Sigrid2DMap();
            
            void setInsertPattern(const std::vector<T>& insertPattern);
            void setSize(const unsigned int& columns, const unsigned int& rows);

            bool addColumnLeft();
            bool addColumnRight();
            bool addRowUp();
            bool addRowDown();
            bool removeColumnLeft();
            bool removeColumnRight();
            bool removeRowUp();
            bool removeRowDown();

            void clear();

            std::optional<std::reference_wrapper<T>> at(const Coord& coord);
            const std::optional<std::reference_wrapper<const T>> at(const Coord& coord) const;

            const unsigned int& numColumns() const;
            const unsigned int& numRows() const;
            const std::vector<T>& getInsertPattern() const;

        private:

            T getInsertElement(const Coord& coord) const;

            void refill();

            void shiftInsertPatternRight();

        unsigned int m_columns = 0;
        unsigned int m_rows = 0;
        std::map<Coord, T> m_map;
        std::vector<T> m_insertPattern;
    };
}