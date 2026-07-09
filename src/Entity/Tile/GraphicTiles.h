#pragma once

#include <optional>

#include "Coord/Coord.h"
#include "List/AutoInsertMappedGrid.h"
#include "Entity/Tile/GraphicTile.h"

namespace sigrid{
    
    class ColorManager;

    class GraphicTiles: public sf::Drawable{
        public:
            GraphicTiles();

            void setColorManagerPtr(ColorManager* const managerPtr);
            void setHighlightColorManagerPtr(ColorManager* const managerPtr);

            void setNumColumns(const int& columns);
            void setNumRows(const int& rows);
            void setTileSize(const sf::Vector2f& tileSize);
            void setTopLeftPosition(const sf::Vector2f& topLeftPosition);

            void setLeftToRight();
            void setRightToLeft();
            void setTopToBottom();
            void setBottomToTop();

            void setTilePosition(const Coord& coord, const sf::Vector2f& position);

            void setTileColor(const Coord& coord, const int& colorId);

            void setHighlightColor(const Coord& coord, const int& colorId);
            void removeHighlight(const Coord& coord);

            void addColumnRight(const std::vector<int>& repeatTileColorIds);
            void addColumnLeft(const std::vector<int>& repeatTileColorIds);
            void removeRightColumn();
            void removeLeftColumn();
            void addRowUp(const std::vector<int>& repeatTileColorIds);
            void addRowDown(const std::vector<int>& repeatTileColorIds);
            void removeTopRow();
            void removeBottomRow();

            void clear();

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

            struct IsSet{
                bool numColumns = false;
                bool numRows = false;
                bool tileSize = false;
                bool topLeftPosition = false;
                bool horizontalOrientation = false;
                bool verticalOrientation = false;
                bool isAllSet();
            };

            IsSet m_isSet;
            bool m_isInitialized = false;

            void init();

            void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

            ColorManager* m_tileColorManagerPtr = nullptr;
            ColorManager* m_highlightColorManagerPtr = nullptr;

            list::AutoInsertMappedGrid<GraphicTile> m_tiles;

            sf::Vector2f m_tileSize = {0.f, 0.f};
            sf::Vector2f m_topLeftPosition = {0.f, 0.f};

            bool m_isLeftToRight = true;
            bool m_isTopToBottom = true;
    };
}