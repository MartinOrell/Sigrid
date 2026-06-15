#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

    class RectangleBorder: public sf::Drawable{

        public:
            RectangleBorder();

            void setThickness(const unsigned int& thickness);

            void setTopLeftPosition(const sf::Vector2f& topLeftPosition);

            void setEnclosedArea(const sf::Vector2f& enclosedArea);

            void setColor(const sf::Color& color);

            void init(const bool& isVisible);

            RectangleBorder& operator =(const RectangleBorder& rhs);

            bool isVisible() const;
            bool isHidden() const;

            float getThickness() const;

            void show();

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
            unsigned int m_thickness = 0;

            sf::Vector2f m_topLeftPosition = {0.f,0.f};
            sf::Vector2f m_enclosedArea = {0.f,0.f};

            std::unique_ptr<sf::RectangleShape> m_left;
            std::unique_ptr<sf::RectangleShape> m_right;
            std::unique_ptr<sf::RectangleShape> m_top;
            std::unique_ptr<sf::RectangleShape> m_bottom;

    };
}