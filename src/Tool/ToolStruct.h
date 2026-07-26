#pragma once

#include "Action/Action.h"
#include "Entity/Icon/LogicIcon.h"

namespace sigrid{

struct ToolStruct{
    LogicIcon icon;
    sigrid_action::Action action;
};

}  // namespace sigrid