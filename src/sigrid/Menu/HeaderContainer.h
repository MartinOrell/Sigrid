#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Menu/MenuItemContainer.h"

namespace sigrid{

struct HeaderContainer{

    bool load(InputStream& is);
    friend std::ostream& operator<<(std::ostream& out, const HeaderContainer& header);

    sigrid::String name;
    sigrid_list::Vector<MenuItemContainer> items;
};

}  // namespace sigrid