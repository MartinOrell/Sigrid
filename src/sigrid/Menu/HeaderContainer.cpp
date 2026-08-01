#include "sigrid/Menu/HeaderContainer.h"

#include "sigrid/Config/LoadNamedContainers.h"

bool sigrid::HeaderContainer::load(InputStream& is){

    if(!sigrid_config::loadNamedContainers<MenuItemContainer>(items, is)){

        std::cerr << "HeaderContainer: Failed to load items."
            << " Failed to load HeaderContainer" << std::endl;
        return false;
    }
    return true;
}