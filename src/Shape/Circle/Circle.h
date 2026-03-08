#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>

#include "../../Coord/Coord.h"
#include "LogicCircle.h"
#include "GraphicCircle.h"

namespace sigrid{

    class Circle: public sf::Drawable{

        public:
            Circle(const Coord& coord, const int colorId, const sf::Vector2f& position, const sf::Color& color, const float& diameter);
            Coord getCoord() const;

            void setPosition(const Coord& coord, const sf::Vector2f& position);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            LogicCircle m_logic;
            GraphicCircle m_graphic;

    };

}