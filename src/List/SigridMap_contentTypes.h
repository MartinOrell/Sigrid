#pragma once

#include "SigridMap.h"

#include <string>
#include <SFML/Graphics/Texture.hpp>

#include "../Coord/CoordPair.h"
#include "../Entity/Shape/Arrow/LogicArrow.h"

// This class is only included by SigridMap.cpp
// Add more templates below to support more types
template class sigrid::SigridMap<std::string, sf::Texture>;
template class sigrid::SigridMap<sigrid::CoordPair, sigrid::LogicArrow>;