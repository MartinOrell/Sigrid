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

std::ostream& sigrid::operator<<(std::ostream& out, const sigrid::HeaderContainer& menu){

    out << menu.name
        << " " << sigrid::ListSaver(menu.items);

    return out;
}