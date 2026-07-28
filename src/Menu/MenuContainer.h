#pragma once

#include <string>

#include "List/Vector.h"
#include "Menu/MenuItemContainer.h"
#include "Menu/HeaderContainer.h"

namespace sigrid{

struct MenuContainer{

    bool load(std::istream& is);

    std::string fontName;
    std::string title;
    sigrid_list::Vector<HeaderContainer> headers;
    bool isPinned;
    bool showItems;

  private:
    bool loadHeaders(std::istream& is);
};

}  // namespace sigrid