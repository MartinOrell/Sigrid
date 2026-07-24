#pragma once

#include <cstdint>

#include <map>

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "List/Vector.h"
#include "Coord/CoordPair.h"

#include "Entity/Piece/PieceContainer.h"
#include "Entity/Piece/PieceColor.h"
#include "Entity/Piece/PieceIdentifier.h"
#include "Entity/Piece/GraphicPiece.h"
#include "Entity/Tile/LogicTile.h"
#include "Entity/Tile/GraphicTile.h"
#include "Board/Board.h"

// This class is only included by Vector.cpp
// Add more templates below to support more types
template class sigrid_list::Vector<int>;
template class sigrid_list::Vector<float>;
template class sigrid_list::Vector<uint32_t>;
template class sigrid_list::Vector<sigrid_coord::CoordPair>;
template class sigrid_list::Vector<sf::Color>;
template class sigrid_list::Vector<sigrid::PieceContainer>;
template class sigrid_list::Vector<sigrid::PieceColor>;
template class sigrid_list::Vector<std::map<sigrid::PieceIdentifier, sigrid::GraphicPiece>>;
template class sigrid_list::Vector<std::map<sigrid::PieceIdentifier, sf::Texture>>;
template class sigrid_list::Vector<sigrid::LogicTile>;
template class sigrid_list::Vector<sigrid::GraphicTile>;
template class sigrid_list::Vector<sigrid::Board>;