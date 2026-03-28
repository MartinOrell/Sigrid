#pragma once

#include <string>

#include <vector>

namespace sigrid{

    struct MenuItemContainer{
        int headerId;
        std::string keyName;
        std::vector<std::string> displayNames;
        std::vector<std::string> actionNames;
    };

    struct MenuContainer{
        std::string fontName;
        std::string title;
        std::vector<std::string> headerNames;
        std::vector<MenuItemContainer> menuItems;
        bool isPinned;
        bool showItems;
        bool showToolWindow;
        bool showColorTools;
    };
}
