#pragma once

#include "List/Sigrid2DMap.h"
#include "Entity/Tile/LogicTile.h"
#include "Entity/Tile/GraphicTile.h"

// This class is only included by Sigrid2DMap.cpp
// Add more templates below to support more types
template class sigrid::list::Sigrid2DMap<sigrid::LogicTile>;
template class sigrid::list::Sigrid2DMap<sigrid::GraphicTile>;