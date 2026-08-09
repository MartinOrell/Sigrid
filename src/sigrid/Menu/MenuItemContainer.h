#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/InputStream/InputStream.h"

namespace sigrid{

struct MenuItemContainer{

    bool load(InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const MenuItemContainer& item);

    sigrid::String name;
    sigrid_list::Vector<sigrid::String> displayNames;
    sigrid_list::Vector<sigrid::String> actionNames;
};

}  // namespace sigrid