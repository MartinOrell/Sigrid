#pragma once

#include <variant>

#include "ToolSelection.h"

#include "../Entity/LogicEntity.h"
#include "../Piece/LogicPiece.h"
#include "../Piece/PieceManager.h"
#include "SFML/Window/Mouse.hpp"


namespace sigrid{

    class Tool{
        public:

            Tool(const ToolSelection& selection);
            const ToolSelection selection() const;
            LogicEntity getEntity() const;
            const int arrowColorId() const;
            void setPiece(const LogicPiece& logicPiece);
            void setSelection(const ToolSelection& selection);
            void setArrow(const int colorId);
            void setCircle(const int colorId);

        private:
            ToolSelection m_selection;
            std::unique_ptr<LogicEntity> m_entity;
            int m_arrowColorId;
            std::vector<sf::RectangleShape> m_square;
    };
}
