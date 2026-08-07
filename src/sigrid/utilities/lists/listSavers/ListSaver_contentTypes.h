#pragma once

#include "sigrid/utilities/lists/listSavers/ListSaver.h"

#include "sigrid/Color/ColorContainer.h"
#include "sigrid/Entity/Piece/PieceColor.h"

template class sigrid::ListSaver<sigrid::ColorContainer>;
template class sigrid::ListSaver<sigrid::PieceColor>;