#pragma once

#include <map>
#include <optional>
#include <vector>

#include "../../Coord/Coord.h"
#include "LogicTile.h"

namespace sigrid{
    class LogicTiles{

        public:
            LogicTiles();

            void init(const int& numColumns, const int& numRows, const std::vector<int>& repeatTileColorIds);

            void setHighlightColor(const Coord& coord, const int& colorId);
            void removeHighlight(const Coord& coord);
            
            int getNumColumns() const;
            int getNumRows() const;

            std::vector<int> getRepeatColorIds() const;

            bool addColumnRight();
            bool addColumnLeft();
            bool removeColumnRight();
            bool removeColumnLeft();
            bool addRowUp();
            bool addRowDown();
            bool removeRowUp();
            bool removeRowDown();

            void clear();

            std::optional<LogicTile> getTile(const Coord& coord) const;

            friend std::ostream& operator<<(std::ostream& out, const LogicTiles& tiles);

        private:

            int m_columns = 0;
            int m_rows = 0;
            std::vector<int> m_repeatTileColorIds;

            std::map<Coord, LogicTile> m_tiles;
    };
}
