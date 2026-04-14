#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

    class RectangleBorder: public sf::Drawable{

        public:
            RectangleBorder();

            void init(const bool& isVisible, const unsigned int& width, const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea);

            RectangleBorder& operator =(const RectangleBorder& rhs);

            bool isVisible() const;

            float getWidth() const;

            void show(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea);

            void hide();

            void addWidth(const float& addedWidth);
            void addHeight(const float& addedHeight);

            void move(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void initLeft(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea);
            void initRight(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea);
            void initTop(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea);
            void initBottom(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea);

            bool m_isVisible;
            unsigned int m_width;
            std::unique_ptr<sf::RectangleShape> m_left;
            std::unique_ptr<sf::RectangleShape> m_right;
            std::unique_ptr<sf::RectangleShape> m_top;
            std::unique_ptr<sf::RectangleShape> m_bottom;

    };
}