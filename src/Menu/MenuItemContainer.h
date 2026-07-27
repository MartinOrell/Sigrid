#pragma once

#include <string>

#include "List/Vector.h"

namespace sigrid{

struct MenuItemContainer{

    bool load(std::istream& is, const std::string& displayName);

    std::string keyName;
    sigrid_list::Vector<std::string> displayNames;
    sigrid_list::Vector<std::string> actionNames;
};

}  // namespace sigrid