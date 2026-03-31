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
#include "../Coord/Coord.h"

#include "../Color/ColorManager.h"

namespace sigrid{
    class GraphicToolPicker: public sf::Drawable{
        public:

            GraphicToolPicker(ColorManager* const squareColorManagerPtr);

            void createGraphic(const sf::Vector2u& size);
            
            void setPosition(const sf::Vector2f& position);

            bool contains(const sf::Vector2f& point) const;

            sf::Vector2u getSize() const;

            unsigned int getNumColumns() const;

            unsigned int getNumRows() const;

            std::optional<Coord> getSquareCoord(const sf::Vector2f& point);

            void addTool(const Coord& coord, const sf::Texture* const texturePtr);

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
            ColorManager* m_squareColorManagerPtr;

            std::map<Coord, sf::RectangleShape> m_tools;
    };
}