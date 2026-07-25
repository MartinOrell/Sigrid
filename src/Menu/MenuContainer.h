#pragma once

#include <string>

#include "List/Vector.h"

namespace sigrid{

struct MenuItemContainer{
    int headerId;
    std::string keyName;
    sigrid_list::Vector<std::string> displayNames;
    sigrid_list::Vector<std::string> actionNames;
};

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
    bool loadMenuItem(std::istream& is, const std::string& displayName);
};

}  // namespace sigrid