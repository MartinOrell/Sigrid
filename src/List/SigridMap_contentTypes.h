#pragma once

#include "SigridMap.h"

#include <string>
#include <SFML/Graphics/Texture.hpp>

// This class is only included by SigridMap.cpp
// Add more templates below to support more types
template class sigrid::SigridMap<std::string, sf::Texture>;