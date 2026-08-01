#pragma once

#include <string>

#include "sigrid/Input/InputStream.h"
#include "sigrid/List/Vector.h"
#include "sigrid/Menu/MenuItemContainer.h"

namespace sigrid{

    struct HeaderContainer{

        bool load(InputStream& is);

        std::string name;
        sigrid_list::Vector<MenuItemContainer> items;
    };
}  // namespace sigrid