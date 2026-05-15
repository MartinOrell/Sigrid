#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>

namespace sf{
    template <typename T> class Vector2;
    using Vector2f = Vector2<float>;
    class Color;
    class CircleShape;
}

namespace sigrid{

    class TurnToken: public sf::Drawable{

        public:
            TurnToken();

            void setRadius(const float& radius);

            void setCenterPosition(const sf::Vector2f& centerPosition);

            void setTurnToMove(const int& turnToMove);

            void init();

            TurnToken& operator =(const TurnToken& rhs);

            bool isVisible() const;

            bool isWithin(const sf::Vector2f& point);

            float getRadius() const;

            sf::Vector2f getCenterPosition() const;

            void show();

            void hide();

            void move(const sf::Vector2f& offset);

        private:

            sf::Color getColor(const int& turnToMove) const;

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            bool m_isVisible = false;
            std::unique_ptr<sf::CircleShape> m_shapePtr;
    };
}