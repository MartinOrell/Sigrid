#pragma once

#include "sigrid/Action/Action.h"
#include "sigrid/Entity/Icon/LogicIcon.h"

namespace sigrid{

struct ToolStruct{
    LogicIcon icon;
    sigrid_action::Action action;
};

}  // namespace sigrid