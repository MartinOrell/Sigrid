#pragma once

#include "List/SigridVector.h"
#include "Coord/CoordPair.h"
#include <SFML/Graphics/Color.hpp>
#include "Entity/Piece/PieceColor.h"
#include <map>
#include "Entity/Piece/PieceIdentifier.h"
#include "Entity/Piece/GraphicPiece.h"
#include <SFML/Graphics/Texture.hpp>

// This class is only included by Sigrid2DMap.cpp
// Add more templates below to support more types
template class sigrid::SigridVector<float>;
template class sigrid::SigridVector<sigrid::CoordPair>;
template class sigrid::SigridVector<sf::Color>;
template class sigrid::SigridVector<sigrid::PieceColor>;
template class sigrid::SigridVector<std::map<sigrid::PieceIdentifier, sigrid::GraphicPiece>>;
template class sigrid::SigridVector<std::map<sigrid::PieceIdentifier, sf::Texture>>;