#pragma once

#include <memory>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

namespace sf{
    class RenderTexture;
}

namespace sigrid{

    class SigridRenderTexture: public sf::Drawable{

        public:

            SigridRenderTexture();

            void setBackgroundColor(const sf::Color& color);
            bool setSize(const sf::Vector2f& size);
            void setPosition(const sf::Vector2f& position);

            sf::Vector2f getPosition() const;
            sf::Vector2f getSize() const;

            bool isInitialized() const;
            bool contains(const sf::Vector2f& point) const;

            void clear();
            void draw(const sf::Drawable& drawable);
            void display();

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            std::unique_ptr<sf::RenderTexture> m_texture;
            std::unique_ptr<sf::Sprite> m_sprite;
            sf::Color m_backgroundColor = sf::Color{255,255,255,0};
            sf::Vector2f m_position;

    };
}

