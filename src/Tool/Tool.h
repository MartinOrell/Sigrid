#pragma once

#include <variant>

#include "ToolSelection.h"

#include "../Piece/Piece.h"
#include "../Piece/PieceManager.h"
#include "SFML/Window/Mouse.hpp"


namespace sigrid{

    class Tool{
        public:

            Tool(const ToolSelection& selection);
            const ToolSelection selection() const;
            const Piece piece() const;
            const int arrowColorId() const;
            const int getCircleColorId() const;
            void setPiece(const Piece& piece);
            void setSelection(const ToolSelection& selection);
            void setArrow(const int colorId);
            void setCircle(const int colorId);

        private:
            ToolSelection m_selection;
            std::unique_ptr<Piece> m_piece;
            int m_arrowColorId;
            int m_circleColorId;
            std::vector<sf::RectangleShape> m_square;
    };
}
