#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

    class Icon: public sf::Drawable{

        public:
            Icon();
            
            void setSize(const sf::Vector2f& size);

            void setPosition(const sf::Vector2f& position);

            void setTexture(const sf::Texture* texturePtr);

            void move(const sf::Vector2f& offset);

        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            sf::RectangleShape m_shape;
    };
}