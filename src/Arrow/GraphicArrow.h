#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>


namespace sigrid{

    class GraphicArrow: public sf::Drawable{

        public:
            GraphicArrow(sf::Vector2f fromPosition, sf::Vector2f toPosition, sf::Color color);
            GraphicArrow(const GraphicArrow&);
            GraphicArrow& operator =(const GraphicArrow&);

            void set(const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition);
            void setColor(sf::Color color);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            
            //Since Convex shape cannot draw concave shapes, multiple shapes are required
            sf::ConvexShape m_line;
            sf::CircleShape m_head;
    };

}