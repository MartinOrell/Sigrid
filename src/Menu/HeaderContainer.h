#pragma once

#include <string>
#include <istream>

#include "List/Vector.h"
#include "Menu/MenuItemContainer.h"

namespace sigrid{

    struct HeaderContainer{

        bool load(std::istream& is);

        std::string name;
        sigrid_list::Vector<MenuItemContainer> items;
    };
}  // namespace sigrid