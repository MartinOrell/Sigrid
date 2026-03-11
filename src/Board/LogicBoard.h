#pragma once

#include <vector>
#include <map>

#include "../Piece/LogicPiece.h"
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <memory>
#include "../Coord/Coord.h"
#include <string>

#include "BoardDataContainer.h"
#include "../Arrow/LogicArrow.h"
#include "../Piece/PieceDataContainer.h"
#include "../Shape/Circle/LogicCircle.h"
#include "../Entity/LogicEntities.h"

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
            std::optional<LogicPiece> getPieceAt(const Coord& coord) const;
            std::optional<LogicCircle> getCircleAt(const Coord& coord) const;
            std::optional<int> getSquareHighlightAt(const Coord& coord) const;
            std::string getFen() const;

            void addPiece(const LogicPiece& piece, const Coord& coord);
            void removePiece(const Coord& coord);
            bool movePiece(const Coord& fromCoord, const Coord& toCoord);

            void addSquareHighlight(const int colorId, const Coord& coord);

            void addArrow(const LogicArrow& arrow);
            void removeArrow(const LogicArrow& arrow);
            void addCircle(const LogicCircle& circle, const Coord& coord);
            void removeCircle(const Coord& coord);

            void print();
            void clear();

            friend std::ostream& operator<<(std::ostream& out, const LogicBoard& board);
        private:
            std::vector<int> m_repeatedSquareIds;
            std::vector<std::vector<int>> m_squareLayer; //colorIds
            LogicEntities m_pieceLayer;
            std::vector<std::vector<std::unique_ptr<int>>> m_squareHighlight; //highlightColorIds
            std::vector<LogicArrow> m_arrows;
    };
}
