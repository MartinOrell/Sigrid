#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace sigrid{

    class GraphicCircle: public sf::Drawable{

        public:
            GraphicCircle(const sf::Vector2f& position, const sf::Color& color, const float& diameter);
            GraphicCircle(const GraphicCircle&);
            GraphicCircle& operator =(const GraphicCircle&);

            void setPosition(const sf::Vector2f& position);
            void setColor(const sf::Color& color);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            
            sf::CircleShape m_shape;

    };

}