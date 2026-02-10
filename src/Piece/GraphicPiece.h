#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>

#include <vector>


namespace sigrid{
    class GraphicPiece: public sf::Drawable{
        public:
            GraphicPiece(sf::Vector2u size, const sf::Texture* texturePtr);
            GraphicPiece(const GraphicPiece&);
            GraphicPiece& operator =(const GraphicPiece&);
            void setPosition(sf::Vector2f);
            bool contains(sf::Vector2i point) const;
            void resize(sf::Vector2f size);

            const sf::Texture getTexture() const;
            const sf::Texture* getTexturePtr() const;

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            sf::Sprite m_sprite;
            sf::Vector2f m_offset;
            const sf::Texture* m_texturePtr;
    };
}
