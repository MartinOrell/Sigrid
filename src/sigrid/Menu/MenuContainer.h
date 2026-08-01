#pragma once

#include <string>

#include "sigrid/Input/InputStream.h"
#include "sigrid/List/Vector.h"
#include "sigrid/Menu/MenuItemContainer.h"
#include "sigrid/Menu/HeaderContainer.h"

namespace sigrid{

struct MenuContainer{

    bool load(InputStream& is);

    std::string fontName;
    std::string title;
    sigrid_list::Vector<HeaderContainer> headers;
    bool isPinned;
    bool showItems;
};

}  // namespace sigrid