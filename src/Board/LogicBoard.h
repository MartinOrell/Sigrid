#pragma once

#include <vector>
#include <optional>
#include <memory>
#include <string>

#include "BoardDataContainer.h"
#include "../Coord/Coord.h"
#include "../Coord/CoordPair.h"
#include "../Entity/LogicEntities.h"
#include "../Arrow/LogicArrow.h"

namespace sigrid{
    class LogicBoard{

        public:
            LogicBoard(const BoardDataContainer& data);
            LogicBoard(const LogicBoard& board);
            ~LogicBoard();
            const unsigned int width() const;
            const unsigned int height() const;

            bool isWithinBoard(const Coord& coord) const;
            bool isEmptySquare(const Coord& coord) const;
            std::optional<int> getSquareColorAt(const Coord& coord) const;
            std::optional<LogicEntity> getEntityAt(const Coord& coord) const;
            std::optional<LogicArrow> getArrowAt(const CoordPair& coordPair) const;
            std::optional<int> getSquareHighlightAt(const Coord& coord) const;
            std::string getFen() const;

            bool addEntity(const Coord& coord, const LogicEntity& entity);
            bool removeEntity(const Coord& coord);
            bool moveEntity(const Coord& fromCoord, const Coord& toCoord);

            bool addSquareHighlight(const Coord& coord, const int colorId);

            bool addArrow(const CoordPair& coordPair, const LogicArrow& arrow);
            bool removeArrow(const CoordPair& coordPair);

            void print();
            void clear();

            friend std::ostream& operator<<(std::ostream& out, const LogicBoard& board);
        private:
            std::vector<int> m_repeatedSquareIds;
            std::vector<std::vector<int>> m_squareLayer; //colorIds
            LogicEntities m_pieceLayer;
            std::vector<std::vector<std::unique_ptr<int>>> m_squareHighlight; //highlightColorIds
            std::map<CoordPair, LogicArrow> m_arrows;
    };
}
