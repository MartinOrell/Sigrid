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

            void setFromPosition(const sf::Vector2f& fromPosition);

            void setToPosition(const sf::Vector2f& toPosition);

            void setPosition(const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition);

            void setColor(const sf::Color& color);

            void setThickness(const float& thickness);

            void setHeadSize(const float& size);

            GraphicArrow& operator =(const GraphicArrow&);

            void setPosition(const sf::Vector2f& position);

            void move(const sf::Vector2f& offset);

        private:

            struct IsSet{
                bool fromPosition = false;
                bool toPosition = false;
                bool thickness = false;
                bool headSize = false;
                bool isAllSet();
            };

            IsSet m_isSet;
            void updateShape();
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            
            //Since Convex shape cannot draw concave shapes, multiple shapes are required
            sf::ConvexShape m_line;
            sf::CircleShape m_head;

            float m_thickness = 0.f;
            float m_headSize = 0.f;

            sf::Vector2f m_toPosition = {0.f, 0.f};
    };

}