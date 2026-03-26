#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

    class GraphicTile: public sf::Drawable{

        public:
            GraphicTile();

            void init(const sf::Vector2f& size, const sf::Color& color);

            void setPosition(const sf::Vector2f& topLeftPosition);

            sf::Vector2f getSize() const;

            sf::Vector2f getTopLeftPosition() const;

            sf::Vector2f getCentrePosition() const;

            float getRightPosition() const;

            float getTopPosition() const;

            GraphicTile& operator =(const GraphicTile&);

            void move(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            
            sf::RectangleShape m_shape;
    };

}