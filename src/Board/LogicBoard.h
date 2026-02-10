#pragma once

#include <vector>

#include "../Piece/LogicPiece.h"
#include <SFML/System/Vector2.hpp>
#include <optional>
#include <memory>
#include "Coord.h"
#include <string>

#include "../Arrow/LogicArrow.h"

namespace sigrid{
    class LogicBoard{

        public:
            LogicBoard(const std::string& filename);
            LogicBoard(const LogicBoard& board);
            ~LogicBoard();
            const unsigned int width() const;
            const unsigned int height() const;

            bool isEmptySquare(const Coord& coord) const;
            std::optional<LogicPiece*> getPieceAt(const Coord& coord) const;
            std::optional<int> getSquareHighlightAt(const Coord& coord) const;

            void addPiece(const LogicPiece& piece, const Coord& coord);
            void removePiece(const Coord& coord);
            bool movePiece(const Coord& fromCoord, const Coord& toCoord);

            void addSquareHighlight(const int colorId, const Coord& coord);

            void addArrow(const LogicArrow& arrow);
            void removeArrow(const LogicArrow& arrow);

            void print();
            void clear();

            void save(const std::string& filename);
        private:
            std::vector<std::vector<int>> m_squareLayer; //colorIds
            std::vector<std::vector<std::unique_ptr<int>>> m_squareHighlight; //highlightColorIds
            std::vector<std::vector<LogicPiece*>> m_pieceLayer;
            std::vector<LogicArrow> m_arrows;
    };
}
