#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/CircleShape.hpp>


namespace sigrid{

    class TurnToken: public sf::Drawable{

        public:
            TurnToken();

            void init(const float& radius, const sf::Vector2f& centerPosition);

            TurnToken& operator =(const TurnToken& rhs);

            bool isVisible() const;

            bool isWithin(const sf::Vector2f& point);

            float getRadius() const;

            sf::Vector2f getCenterPosition() const;

            void show();

            void hide();

            void toggle();

            void move(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            bool m_isVisible;
            std::unique_ptr<sf::CircleShape> m_shapePtr;
    };
}