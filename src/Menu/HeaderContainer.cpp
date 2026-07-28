#include "Menu/HeaderContainer.h"

#include "Config/LoadNamedContainers.h"

bool sigrid::HeaderContainer::load(std::istream& is){
    return sigrid_config::loadNamedContainers<MenuItemContainer>(items, is);
}