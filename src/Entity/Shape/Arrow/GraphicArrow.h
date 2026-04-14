#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/Graphics/CircleShape.hpp>

namespace sf{
    class Color;
}

namespace sigrid{

    class GraphicArrow: public sf::Drawable{

        public:
            GraphicArrow();

            void init(const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const sf::Color& color, const float& thickness, const float& headSize);

            GraphicArrow& operator =(const GraphicArrow&);

            void set(const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition);
            void setColor(const sf::Color& color);

            void move(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            
            //Since Convex shape cannot draw concave shapes, multiple shapes are required
            sf::ConvexShape m_line;
            sf::CircleShape m_head;

            float m_thickness;
            float m_headSize;
    };

}