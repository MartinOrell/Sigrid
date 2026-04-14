#pragma once

#include <map>
#include <optional>

#include "../../Coord/Coord.h"
#include "GraphicTile.h"

namespace sigrid{
    
    class ColorManager;

    class GraphicTiles: public sf::Drawable{
        public:
            GraphicTiles();

            void init(const int& columns, const int& rows, const sf::Vector2f& tileSize, ColorManager* const tileColorManagerPtr, ColorManager* const highlightColorManagerPtr, const sf::Vector2f& topLeftPosition, const bool& isLeftToRight, const bool& isTopToBottom);

            void setTilePosition(const Coord& coord, const sf::Vector2f& position);

            void setTileColor(const Coord& coord, const int& colorId);

            void setHighlightColor(const Coord& coord, const int& colorId);
            void removeHighlight(const Coord& coord);

            void addColumnRight(const std::vector<int>& repeatTileColorIds, const bool& isLeftToRight);
            void addColumnLeft(const std::vector<int>& repeatTileColorIds, const bool& isLeftToRight);
            void removeColumnRight(const bool& isLeftToRight);
            void removeColumnLeft(const bool& isLeftToRight);
            void addRowUp(const std::vector<int>& repeatTileColorIds, const bool& isTopToBottom);
            void addRowDown(const std::vector<int>& repeatTileColorIds, const bool& isTopToBottom);
            void removeRowUp(const bool& isTopToBottom);
            void removeRowDown(const bool& isTopToBottom);

            int getNumColumns() const;
            int getNumRows() const;

            float getTileWidth() const;
            float getTileHeight() const;
            sf::Vector2f getTileSize() const;
            
            std::optional<sf::Vector2f> getTileTopLeftPosition(const Coord& coord) const;
            std::optional<sf::Vector2f> getTileCentrePosition(const Coord& coord) const;
            std::optional<float> getTileRightPosition(const Coord& coord) const;
            std::optional<float> getTileTopPosition(const Coord& coord) const;

            std::optional<sf::Color> getTileColor(const Coord& coord) const;

            void move(const sf::Vector2f& offset);

        private:
            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            ColorManager* m_tileColorManagerPtr;
            ColorManager* m_highlightColorManagerPtr;

            int m_columns;
            int m_rows;

            sf::Vector2f m_tileSize;

            std::map<Coord, GraphicTile> m_tiles;
    };
}