#pragma once

#include "sigrid/utilities/lists/listSavers/ListSaver.h"

#include "sigrid/Color/ColorContainer.h"
#include "sigrid/Entity/Piece/PieceColor.h"
#include "sigrid/Entity/Piece/PieceContainer.h"
#include "sigrid/Menu/HeaderContainer.h"
#include "sigrid/Menu/MenuItemContainer.h"
#include "sigrid/ToolPicker/ToolBlockContainer.h"
#include "sigrid/Board/BoardLabelContainer.h"
#include "sigrid/Board/BoardContainer.h"

template class sigrid::ListSaver<sigrid::ColorContainer>;
template class sigrid::ListSaver<sigrid::PieceColor>;
template class sigrid::ListSaver<sigrid::PieceContainer>;
template class sigrid::ListSaver<sigrid::HeaderContainer>;
template class sigrid::ListSaver<sigrid::MenuItemContainer>;
template class sigrid::ListSaver<sigrid::ToolBlockContainer>;
template class sigrid::ListSaver<sigrid::BoardLabelContainer>;
template class sigrid::ListSaver<sigrid::BoardContainer>;