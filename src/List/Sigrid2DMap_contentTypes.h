#pragma once

#include "Sigrid2DMap.h"
#include "../Entity/Tile/LogicTile.h"

// This class is only included by Sigrid2DMap.cpp
// Add more templates below to support more types
template class sigrid::Sigrid2DMap<sigrid::LogicTile>;