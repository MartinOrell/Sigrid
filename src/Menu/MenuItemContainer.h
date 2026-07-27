#pragma once

#include <string>

#include "List/Vector.h"

namespace sigrid{

struct MenuItemContainer{
    int headerId;
    std::string keyName;
    sigrid_list::Vector<std::string> displayNames;
    sigrid_list::Vector<std::string> actionNames;
};

}  // namespace sigrid