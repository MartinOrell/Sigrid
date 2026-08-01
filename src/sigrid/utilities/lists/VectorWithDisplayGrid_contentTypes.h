#pragma once

#include "sigrid/utilities/lists/VectorWithDisplayGrid.h"
#include "sigrid/Board/Board.h"

// This class is only included by VectorWithDisplayGrid.cpp
// Add more templates below to support more types
template class sigrid_list::VectorWithDisplayGrid<sigrid::Board>;