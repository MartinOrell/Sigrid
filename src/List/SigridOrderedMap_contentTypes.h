#pragma once

#include "SigridOrderedMap.h"
#include "../Coord/CoordPair.h"
#include "../Entity/Shape/Arrow/GraphicArrow.h"

// This class is only included by SigridOrderedMap.cpp
// Add more templates below to support more types
template class sigrid::SigridOrderedMap<sigrid::CoordPair, sigrid::GraphicArrow>;