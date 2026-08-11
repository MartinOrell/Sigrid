#include "sigrid/Menu/HeaderContainer.h"

#include "sigrid/utilities/lists/listLoaders/LoadNamedContainers.h"
#include "sigrid/utilities/lists/listSavers/ListSaver.h"

bool sigrid::HeaderContainer::load(InputStream& is){

    if(!sigrid::loadNamedContainers<MenuItemContainer>(items, is)){

        std::cerr << "HeaderContainer: Failed to load items."
            << " Failed to load HeaderContainer" << std::endl;
        return false;
    }
    return true;
}

sigrid::String sigrid::HeaderContainer::getString(const int& indentLevel) const{

    sigrid::String out;
    out.append(this->name);
    out.append(" ");
    out.append(sigrid::ListSaver(this->items).getMultiLineString(indentLevel));

    return out;
}