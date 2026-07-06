#pragma once

#include <memory>

#include "Tool/ToolSelection.h"
#include "Entity/LogicEntity.h"

namespace sigrid{

    struct ToolContainer;

    class Tool{
        public:

            Tool();
            Tool(const Tool& src);
            Tool(const ToolContainer& data);
            Tool& operator=(const Tool& rhs);
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
    };
}
