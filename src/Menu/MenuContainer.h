#pragma once

#include <string>

#include "List/Vector.h"
#include "Menu/MenuItemContainer.h"

namespace sigrid{

struct MenuContainer{

    bool load(std::istream& is);

    std::string fontName;
    std::string title;
    sigrid_list::Vector<std::string> headerNames;
    sigrid_list::Vector<MenuItemContainer> menuItems;
    bool isPinned;
    bool showItems;

  private:
    bool loadHeaders(std::istream& is);
    bool loadHeaderItems(std::istream& is);
};

}  // namespace sigrid