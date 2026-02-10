#pragma once

#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>

#include "../Board/LogicBoard.h"

#include <vector>
#include <map>
#include <optional>
#include <memory>
#include "../Board/Coord.h"


namespace sigrid{
    class GraphicToolPicker: public sf::Drawable{
        public:

            GraphicToolPicker(const std::vector<sf::Color> squareColors);

            void createGraphic(const sf::Vector2u& size);
            
            void setPosition(const sf::Vector2f&);

            bool contains(sf::Vector2i point) const;

            sf::Vector2u getSize() const;

            unsigned int getNumColumns() const;

            unsigned int getNumRows() const;

            std::optional<Coord> getSquareCoord(sf::Vector2i point);

            void addTool(const sf::Texture* texturePtr, const Coord& coord);

            void removeTool(const Coord& coord);

            void moveTool(const Coord& fromCoord, const Coord& toCoord);

            void removeLastColumn();

            void redrawTexture();

            void clear();

        private:

            void addSquareRow();

            void addSquareColumn();

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            sf::Vector2f m_squareSize;

            sf::RenderTexture m_texture;
            sf::Vector2f m_position;
            std::vector<std::vector<std::unique_ptr<sf::RectangleShape>>> m_squares;

            

            float m_offsetY;

            sf::Color m_backgroundColor;
            std::vector<sf::Color> m_squareColors;

            std::map<Coord, sf::RectangleShape> m_tools;
    };
}