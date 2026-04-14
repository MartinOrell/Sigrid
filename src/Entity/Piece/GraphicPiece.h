#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sigrid{
    class GraphicPiece: public sf::Drawable{
        public:
            GraphicPiece(sf::Vector2u size, const sf::Texture* const texturePtr);
            GraphicPiece(const GraphicPiece&);
            GraphicPiece& operator =(const GraphicPiece&);
            void setPosition(sf::Vector2f);
            bool contains(sf::Vector2i point) const;
            void resize(sf::Vector2f size);

            const sf::Texture getTexture() const;
            const sf::Texture* getTexturePtr() const;

            void move(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            sf::Sprite m_sprite;
            const sf::Texture* m_texturePtr;
    };
}
