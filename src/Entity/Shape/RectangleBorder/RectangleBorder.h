#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

    class RectangleBorder: public sf::Drawable{

        public:
            RectangleBorder();

            void setWidth(const unsigned int& width);

            void setTopLeftPosition(const sf::Vector2f& topLeftPosition);

            void setEnclosedArea(const sf::Vector2f& enclosedArea);

            void init(const bool& isVisible);

            RectangleBorder& operator =(const RectangleBorder& rhs);

            bool isVisible() const;
            bool isHidden() const;

            float getWidth() const;

            void show(const sf::Vector2f& topLeftPosition, const sf::Vector2f& enclosedArea);

            void hide();

            void addWidth(const float& addedWidth);
            void addHeight(const float& addedHeight);

            void move(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            void initLeft();
            void initRight();
            void initTop();
            void initBottom();

            bool m_isVisible = true;
            unsigned int m_width = 0;

            sf::Vector2f m_topLeftPosition = {0.f,0.f};
            sf::Vector2f m_enclosedArea = {0.f,0.f};

            std::unique_ptr<sf::RectangleShape> m_left;
            std::unique_ptr<sf::RectangleShape> m_right;
            std::unique_ptr<sf::RectangleShape> m_top;
            std::unique_ptr<sf::RectangleShape> m_bottom;

    };
}