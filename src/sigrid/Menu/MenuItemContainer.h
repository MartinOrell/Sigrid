#pragma once

#include <string>

#include "sigrid/List/Vector.h"
#include "sigrid/Input/InputStream.h"

namespace sigrid{

struct MenuItemContainer{

    bool load(InputStream& is);

    std::string name;
    sigrid_list::Vector<std::string> displayNames;
    sigrid_list::Vector<std::string> actionNames;
};

}  // namespace sigrid