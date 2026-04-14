#pragma once

#include <memory>

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

namespace sigrid{

    class GraphicTile: public sf::Drawable{

        public:
            GraphicTile();
            GraphicTile(const GraphicTile& src);

            void init(const sf::Vector2f& size, const sf::Color& color);

            void setPosition(const sf::Vector2f& topLeftPosition);

            void setTileColor(const sf::Color& color);

            void setHighlightColor(const sf::Color& color);

            void removeHighlight();

            sf::Vector2f getSize() const;

            sf::Vector2f getTopLeftPosition() const;

            sf::Vector2f getCentrePosition() const;

            float getRightPosition() const;

            float getTopPosition() const;

            sf::Color getColor() const;

            GraphicTile& operator =(const GraphicTile&);

            void move(const sf::Vector2f& offset);

        private:

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            
            sf::RectangleShape m_shape;
            std::unique_ptr<sf::RectangleShape> m_highlightPtr;
    };

}