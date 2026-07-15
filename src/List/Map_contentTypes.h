#pragma once

#include "List/Map.h"

#include <string>
#include <optional>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>

#include "Coord/Coord.h"
#include "Coord/CoordPair.h"
#include "Action/Action.h"
#include "Tool/Tool.h"
#include "Entity/Piece/PieceIdentifier.h"
#include "Entity/Tile/LogicTile.h"
#include "Entity/Piece/LogicPiece.h"
#include "Entity/Shape/Circle/LogicCircle.h"
#include "Entity/Shape/Arrow/LogicArrow.h"
#include "Entity/Icon/Icon.h"
#include "Entity/Tile/GraphicTile.h"
#include "Entity/Piece/GraphicPiece.h"
#include "Entity/Shape/Circle/GraphicCircle.h"
#include "Entity/Shape/Arrow/GraphicArrow.h"
#include "Entity/Icon/LogicIcon.h"
#include "Menu/Menu.h"
#include "Menu/MenuItem.h"

// This class is only included by Map.cpp
// Add more templates below to support more types
template class sigrid_list::Map<std::string, sf::Texture>;
template class sigrid_list::Map<std::string, sf::Font>;
template class sigrid_list::Map<sigrid::PieceIdentifier, std::string>;
template class sigrid_list::Map<sigrid_coord::CoordPair, sigrid::LogicArrow>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::GraphicTile>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::GraphicPiece>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::GraphicCircle>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::GraphicArrow>;
template class sigrid_list::Map<sigrid_coord::CoordPair, sigrid::GraphicArrow>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::Icon>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::LogicTile>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::LogicPiece>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::LogicCircle>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::LogicArrow>;
template class sigrid_list::Map<sigrid_coord::Coord, sigrid::LogicIcon>;
template class sigrid_list::Map<sf::Mouse::Button, std::optional<sf::Vector2f>>;
template class sigrid_list::Map<sf::Mouse::Button, sigrid::Tool>;
template class sigrid_list::Map<sf::Keyboard::Key, sigrid_action::Action>;
template class sigrid_list::Map<int, sigrid_coord::CoordPair>;
template class sigrid_list::Map<std::string, sigrid::MenuItem>;
template class sigrid_list::Map<std::string, sigrid::Menu::LayoutItem>;