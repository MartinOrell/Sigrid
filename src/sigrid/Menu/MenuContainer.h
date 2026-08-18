#pragma once

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/InputStream/InputStream.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/Menu/MenuItemContainer.h"
#include "sigrid/Menu/HeaderContainer.h"

namespace sigrid{

struct MenuContainer{

    bool load(InputStream& is);
    sigrid::String getString(const int& indentLevel) const;

    sigrid::String fontName;
    sigrid::String title;
    sigrid_list::Vector<HeaderContainer> headers;
    bool isPinned;
    bool showItems;
};

}  // namespace sigrid