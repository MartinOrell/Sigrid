#pragma once

#include <string>

#include <vector>

#include "List/Vector.h"

namespace sigrid{

struct MenuItemContainer{
    int headerId;
    std::string keyName;
    sigrid_list::Vector<std::string> displayNames;
    std::vector<std::string> actionNames;
};

struct MenuContainer{

    bool load(std::istream& is);

    std::string fontName;
    std::string title;
    std::vector<std::string> headerNames;
    std::vector<MenuItemContainer> menuItems;
    bool isPinned;
    bool showItems;

  private:
    bool loadHeaders(std::istream& is);
    bool loadHeaderItems(std::istream& is);
    bool loadMenuItem(std::istream& is, const std::string& displayName);
};

}  // namespace sigrid