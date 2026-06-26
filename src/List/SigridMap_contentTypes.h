#pragma once

#include "SigridMap.h"

#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "../Coord/Coord.h"
#include "../Coord/CoordPair.h"
#include "../Entity/Shape/Arrow/LogicArrow.h"
#include "../Entity/Piece/GraphicPiece.h"
#include "../Entity/Shape/Circle/GraphicCircle.h"
#include "../Entity/Shape/Arrow/GraphicArrow.h"
#include "../Entity/Icon/Icon.h"

// This class is only included by SigridMap.cpp
// Add more templates below to support more types
template class sigrid::SigridMap<std::string, sf::Texture>;
template class sigrid::SigridMap<sigrid::CoordPair, sigrid::LogicArrow>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::GraphicPiece>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::GraphicCircle>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::GraphicArrow>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::Icon>;