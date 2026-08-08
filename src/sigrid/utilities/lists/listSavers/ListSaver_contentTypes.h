#pragma once

#include "sigrid/utilities/lists/listSavers/ListSaver.h"

#include "sigrid/Color/ColorContainer.h"
#include "sigrid/Entity/Piece/PieceColor.h"
#include "sigrid/Entity/Piece/PieceContainer.h"
#include "sigrid/Menu/HeaderContainer.h"

template class sigrid::ListSaver<sigrid::ColorContainer>;
template class sigrid::ListSaver<sigrid::PieceColor>;
template class sigrid::ListSaver<sigrid::PieceContainer>;
template class sigrid::ListSaver<sigrid::HeaderContainer>;