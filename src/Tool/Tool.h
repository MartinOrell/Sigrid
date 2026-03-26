#pragma once

#include <memory>
#include <variant>

#include "ToolSelection.h"

#include "../Entity/LogicEntity.h"
#include "SFML/Window/Mouse.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include "ToolContainer.h"


namespace sigrid{

    class Tool{
        public:

            Tool(const ToolContainer& data);
            const ToolSelection selection() const;
            LogicEntity getEntity() const;
            int getArrowColorId() const;
            void setEntity(const LogicEntity& entity);
            void setSelection(const ToolSelection& selection);
            void setArrow(const int colorId);

        private:
            ToolSelection m_selection;
            std::unique_ptr<LogicEntity> m_entity;
            int m_arrowColorId;
            std::vector<sf::RectangleShape> m_square;
    };
}
