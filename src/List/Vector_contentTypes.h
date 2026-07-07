#pragma once

#include "List/Vector.h"
#include "Coord/CoordPair.h"
#include <SFML/Graphics/Color.hpp>
#include "Entity/Piece/PieceColor.h"
#include <map>
#include "Entity/Piece/PieceIdentifier.h"
#include "Entity/Piece/GraphicPiece.h"
#include <SFML/Graphics/Texture.hpp>
#include "Entity/Tile/LogicTile.h"
#include "Entity/Tile/GraphicTile.h"

// This class is only included by Vector.cpp
// Add more templates below to support more types
template class sigrid::list::Vector<float>;
template class sigrid::list::Vector<sigrid::CoordPair>;
template class sigrid::list::Vector<sf::Color>;
template class sigrid::list::Vector<sigrid::PieceColor>;
template class sigrid::list::Vector<std::map<sigrid::PieceIdentifier, sigrid::GraphicPiece>>;
template class sigrid::list::Vector<std::map<sigrid::PieceIdentifier, sf::Texture>>;
template class sigrid::list::Vector<sigrid::LogicTile>;
template class sigrid::list::Vector<sigrid::GraphicTile>;