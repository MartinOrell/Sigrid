#pragma once

#include "List/VectorWithDisplayGrid.h"
#include "Board/Board.h"

// This class is only included by VectorWithDisplayGrid.cpp
// Add more templates below to support more types
template class sigrid::list::VectorWithDisplayGrid<sigrid::Board>;