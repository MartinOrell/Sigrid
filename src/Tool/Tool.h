#pragma once

#include <optional>

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