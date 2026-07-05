#pragma once

#include "SigridMap.h"

#include <string>
#include <optional>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "../Coord/Coord.h"
#include "../Coord/CoordPair.h"
#include "../Action/Action.h"
#include "../Tool/Tool.h"
#include "../Entity/Piece/PieceIdentifier.h"
#include "../Entity/Piece/LogicPiece.h"
#include "../Entity/Shape/Circle/LogicCircle.h"
#include "../Entity/Shape/Arrow/LogicArrow.h"
#include "../Entity/Icon/Icon.h"
#include "../Entity/Piece/GraphicPiece.h"
#include "../Entity/Shape/Circle/GraphicCircle.h"
#include "../Entity/Shape/Arrow/GraphicArrow.h"
#include "../Entity/Icon/LogicIcon.h"
#include "../Menu/Menu.h"
#include "../Menu/MenuItem.h"

// This class is only included by SigridMap.cpp
// Add more templates below to support more types
template class sigrid::SigridMap<std::string, sf::Texture>;
template class sigrid::SigridMap<std::string, sf::Font>;
template class sigrid::SigridMap<sigrid::PieceIdentifier, std::string>;
template class sigrid::SigridMap<sigrid::CoordPair, sigrid::LogicArrow>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::GraphicPiece>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::GraphicCircle>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::GraphicArrow>;
template class sigrid::SigridMap<sigrid::CoordPair, sigrid::GraphicArrow>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::Icon>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::LogicPiece>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::LogicCircle>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::LogicArrow>;
template class sigrid::SigridMap<sigrid::Coord, sigrid::LogicIcon>;
template class sigrid::SigridMap<sf::Mouse::Button, std::optional<sf::Vector2f>>;
template class sigrid::SigridMap<sf::Mouse::Button, sigrid::Tool>;
template class sigrid::SigridMap<sf::Keyboard::Key, sigrid::Action>;
template class sigrid::SigridMap<unsigned int, sigrid::CoordPair>;
template class sigrid::SigridMap<std::string, sigrid::MenuItem>;
template class sigrid::SigridMap<std::string, sigrid::Menu::LayoutItem>;