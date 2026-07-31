#include "Menu/HeaderContainer.h"

#include "Config/LoadNamedContainers.h"

bool sigrid::HeaderContainer::load(std::istream& is){

    if(!sigrid_config::loadNamedContainers<MenuItemContainer>(items, is)){

        std::cerr << "HeaderContainer: Failed to load items."
            << " Failed to load HeaderContainer" << std::endl;
        return false;
    }
    return true;
}