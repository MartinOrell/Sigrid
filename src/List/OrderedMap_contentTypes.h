#pragma once

#include "List/OrderedMap.h"
#include "Coord/CoordPair.h"
#include "Entity/Shape/Arrow/LogicArrow.h"
#include "Entity/Shape/Arrow/GraphicArrow.h"

// This class is only included by OrderedMap.cpp
// Add more templates below to support more types
template class sigrid::list::OrderedMap<sigrid::CoordPair, sigrid::LogicArrow>;
template class sigrid::list::OrderedMap<sigrid::CoordPair, sigrid::GraphicArrow>;