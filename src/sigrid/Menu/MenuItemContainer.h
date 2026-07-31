#pragma once

#include <string>

#include "sigrid/List/Vector.h"

namespace sigrid{

struct MenuItemContainer{

    bool load(std::istream& is);

    std::string name;
    sigrid_list::Vector<std::string> displayNames;
    sigrid_list::Vector<std::string> actionNames;
};

}  // namespace sigrid