#pragma once

#include <map>

#include <SFML/Graphics/Texture.hpp>

#include "sigrid/utilities/String/String.h"
#include "sigrid/utilities/lists/Vector.h"
#include "sigrid/utilities/Coord/CoordPair.h"
#include "sigrid/utilities/Coord/CoordBlock.h"
#include "sigrid/utilities/GraphicText/GraphicText.h"
#include "sigrid/utilities/Color/Color.h"

#include "sigrid/Color/ColorContainer.h"
#include "sigrid/Entity/Piece/PieceContainer.h"
#include "sigrid/Entity/Piece/PieceDataContainer.h"
#include "sigrid/Entity/Piece/PieceColor.h"
#include "sigrid/Entity/Piece/PieceIdentifier.h"
#include "sigrid/Entity/Piece/GraphicPiece.h"
#include "sigrid/Entity/Shape/Circle/CircleDataContainer.h"
#include "sigrid/Entity/Shape/Arrow/ArrowDataContainer.h"
#include "sigrid/Entity/Tile/LogicTile.h"
#include "sigrid/Entity/Tile/GraphicTile.h"
#include "sigrid/Board/Board.h"
#include "sigrid/Board/BoardLabelContainer.h"
#include "sigrid/Menu/MenuContainer.h"
#include "sigrid/Menu/HeaderContainer.h"
#include "sigrid/Tool/ToolStruct.h"
#include "sigrid/ToolPicker/ToolBlockContainer.h"

// This class is only included by Vector.cpp
// Add more templates below to support more types
template class sigrid_list::Vector<int>;
template class sigrid_list::Vector<float>;
template class sigrid_list::Vector<sigrid::String>;
template class sigrid_list::Vector<sigrid_coord::CoordPair>;
template class sigrid_list::Vector<sigrid_coord::CoordBlock>;
template class sigrid_list::Vector<sigrid::Color>;
template class sigrid_list::Vector<sigrid::GraphicText>;
template class sigrid_list::Vector<sigrid::ColorContainer>;
template class sigrid_list::Vector<sigrid::PieceContainer>;
template class sigrid_list::Vector<sigrid::PieceDataContainer>;
template class sigrid_list::Vector<sigrid::PieceColor>;
template class sigrid_list::Vector<std::map<sigrid::PieceIdentifier, sigrid::GraphicPiece>>;
template class sigrid_list::Vector<std::map<sigrid::PieceIdentifier, sf::Texture>>;
template class sigrid_list::Vector<sigrid::CircleDataContainer>;
template class sigrid_list::Vector<sigrid::ArrowDataContainer>;
template class sigrid_list::Vector<sigrid::LogicTile>;
template class sigrid_list::Vector<sigrid::GraphicTile>;
template class sigrid_list::Vector<sigrid::Board>;
template class sigrid_list::Vector<sigrid::BoardLabelContainer>;
template class sigrid_list::Vector<sigrid::HeaderContainer>;
template class sigrid_list::Vector<sigrid::MenuItemContainer>;
template class sigrid_list::Vector<sigrid::ToolStruct>;
template class sigrid_list::Vector<sigrid::ToolBlockContainer>;
template class sigrid_list::Vector<sigrid::BoardContainer>;