#pragma once

#include <string>

#include "List/Vector.h"
#include "Menu/MenuItemContainer.h"

namespace sigrid{

    struct HeaderContainer{
        std::string name;
        sigrid_list::Vector<MenuItemContainer> items;
    };
}  // namespace sigrid