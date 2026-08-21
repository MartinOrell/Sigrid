#pragma once

#include "sigrid/utilities/lists/Vector.h"

#include "sigrid/utilities/String/String.h"

// This class is only included by Vector2D.cpp
// Add more templates below to support more types
template class sigrid_list::Vector2D<sigrid::String>;