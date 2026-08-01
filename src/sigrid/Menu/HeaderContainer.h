#pragma once

#include <string>

#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Menu/MenuItemContainer.h"

namespace sigrid{

    struct HeaderContainer{

        bool load(InputStream& is);

        std::string name;
        sigrid_list::Vector<MenuItemContainer> items;
    };
}  // namespace sigrid