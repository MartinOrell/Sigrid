#pragma once

#include "List/AutoInsertMappedGrid.h"
#include "Entity/Tile/LogicTile.h"
#include "Entity/Tile/GraphicTile.h"

// This class is only included by AutoInsertMappedGrid.cpp
// Add more templates below to support more types
template class sigrid_list::AutoInsertMappedGrid<sigrid::LogicTile>;
template class sigrid_list::AutoInsertMappedGrid<sigrid::GraphicTile>;