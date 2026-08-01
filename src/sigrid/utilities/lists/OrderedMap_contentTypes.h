#pragma once

#include "sigrid/utilities/lists/OrderedMap.h"
#include "sigrid/utilities/Coord/CoordPair.h"
#include "sigrid/Entity/Shape/Arrow/LogicArrow.h"
#include "sigrid/Entity/Shape/Arrow/GraphicArrow.h"

// This class is only included by OrderedMap.cpp
// Add more templates below to support more types
template class sigrid_list::OrderedMap<sigrid_coord::CoordPair, sigrid::LogicArrow>;
template class sigrid_list::OrderedMap<sigrid_coord::CoordPair, sigrid::GraphicArrow>;