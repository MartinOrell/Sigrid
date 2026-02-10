#pragma once

#include "LogicArrow.h"
#include "GraphicArrow.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>

namespace sigrid{

    class Arrow: public sf::Drawable{

        public:
            Arrow(const Coord& fromCoord, const Coord& toCoord, const int colorId, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const sf::Color& color);
            Coord fromCoord() const;
            Coord toCoord() const;

            void set(const Coord& fromCoord, const Coord& toCoord, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            LogicArrow m_logicArrow;
            GraphicArrow m_graphicArrow;

    };

}