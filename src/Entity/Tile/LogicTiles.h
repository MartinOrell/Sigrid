#pragma once

#include <optional>
#include <vector>

#include "Coord/Coord.h"
#include "List/Sigrid2DMap.h"
#include "Entity/Tile/LogicTile.h"

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
            bool removeRightColumn();
            bool removeLeftColumn();
            bool addRowUp();
            bool addRowDown();
            bool removeTopRow();
            bool removeBottomRow();

            void clear();

            std::optional<LogicTile> getTile(const Coord& coord) const;

            friend std::ostream& operator<<(std::ostream& out, const LogicTiles& tiles);

        private:

            list::Sigrid2DMap<LogicTile> m_tiles;
    };
}
