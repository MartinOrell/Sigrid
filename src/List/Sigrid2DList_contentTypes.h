#pragma once

#include "List/Sigrid2DList.h"
#include "Board/Board.h"

// This class is only included by Sigrid2DList.cpp
// Add more templates below to support more types
template class sigrid::list::Sigrid2DList<sigrid::Board>;