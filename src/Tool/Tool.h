#pragma once

#include <optional>

#include "Tool/ToolSelection.h"
#include "Entity/LogicEntity.h"

namespace sigrid{

struct ToolContainer;

class Tool{

  public:

    Tool() = default;
    Tool(const Tool&) = default;
    Tool(Tool&&) = default;
    Tool& operator=(const Tool&) = default;
    Tool& operator=(Tool&&) = default;

    Tool(const ToolContainer& data);
    
    const ToolSelection selection() const;
    std::optional<LogicEntity> getEntity() const;
    int getArrowColorId() const;
    void setEntity(const LogicEntity& entity);
    void setSelection(const ToolSelection& selection);
    void setArrow(const int colorId);

  private:

    ToolSelection m_selection;
    std::optional<LogicEntity> m_entity_o;
    int m_arrowColorId;
};

}  // namespace sigrid