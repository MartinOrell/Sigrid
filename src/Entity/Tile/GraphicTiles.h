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

            void addColorManager(ColorManager* const tileColorManagerPtr);
            void addHighlightColorManager(ColorManager* const highlightColorManagerPtr);

            void setNumColumns(const int& columns);
            void setNumRows(const int& rows);
            void setTileSize(const sf::Vector2f& tileSize);
            void setTopLeftPosition(const sf::Vector2f& topLeftPosition);

            void init(const bool& isLeftToRight, const bool& isTopToBottom);

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

            ColorManager* m_tileColorManagerPtr = nullptr;
            ColorManager* m_highlightColorManagerPtr = nullptr;

            int m_columns = 0;
            int m_rows = 0;

            sf::Vector2f m_tileSize = {0.f, 0.f};
            sf::Vector2f m_topLeftPosition = {0.f, 0.f};

            std::map<Coord, GraphicTile> m_tiles;
    };
}