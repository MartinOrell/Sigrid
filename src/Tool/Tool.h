#pragma once

#include <variant>

#include "ToolSelection.h"

#include "../Piece/LogicPiece.h"
#include "../Piece/PieceManager.h"
#include "SFML/Window/Mouse.hpp"


namespace sigrid{

    class Tool{
        public:

            Tool(const ToolSelection& selection);
            const ToolSelection selection() const;
            LogicPiece getLogicPiece() const;
            const int arrowColorId() const;
            const int getCircleColorId() const;
            void setPiece(const LogicPiece& logicPiece);
            void setSelection(const ToolSelection& selection);
            void setArrow(const int colorId);
            void setCircle(const int colorId);

        private:
            ToolSelection m_selection;
            std::unique_ptr<LogicPiece> m_logicPiece;
            int m_arrowColorId;
            int m_circleColorId;
            std::vector<sf::RectangleShape> m_square;
    };
}
