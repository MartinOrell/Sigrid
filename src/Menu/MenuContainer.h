#pragma once

#include <string>

#include <vector>

namespace sigrid{

    struct MenuItemContainer{
        int headerId;
        std::string displayName;
        std::string actionName;
    };

    struct MenuToggleItemContainer{
        std::string keyName;
        int headerId;
        std::string displayNameOn;
        std::string actionNameOn;
        std::string displayNameOff;
        std::string actionNameOff;
    };

    struct MenuContainer{
        std::string fontName;
        std::string title;
        std::vector<std::string> headerNames;
        std::vector<MenuItemContainer> menuItems;
        std::vector<MenuToggleItemContainer> menuToggleItems;
        bool isPinned;
        bool showItems;
        bool showToolWindow;
        bool showColorTools;
    };
}
