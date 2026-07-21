#pragma once

#include <optional>

#include "Coord/Coord.h"
#include "List/AutoInsertMappedGrid.h"
#include "Entity/Tile/GraphicTile.h"

namespace sigrid{
    
class ColorManager;

class GraphicTiles: public sf::Drawable{

  public:

    GraphicTiles() = default;
    GraphicTiles(const GraphicTiles&) = default;
    GraphicTiles(GraphicTiles&&) = default;
    GraphicTiles& operator=(const GraphicTiles&) = default;
    GraphicTiles& operator=(GraphicTiles&&) = default;

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

    void insertAllTiles();

    void setTilePosition(const sigrid_coord::Coord& coord, const sf::Vector2f& position);

    void setTileColor(const sigrid_coord::Coord& coord, const int& colorId);

    void setHighlightColor(const sigrid_coord::Coord& coord, const int& colorId);
    void removeHighlight(const sigrid_coord::Coord& coord);

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
    
    std::optional<sf::Vector2f> getTileTopLeftPosition(const sigrid_coord::Coord& coord) const;
    std::optional<sf::Vector2f> getTileCentrePosition(const sigrid_coord::Coord& coord) const;
    std::optional<float> getTileRightPosition(const sigrid_coord::Coord& coord) const;
    std::optional<float> getTileTopPosition(const sigrid_coord::Coord& coord) const;

    std::optional<sf::Color> getTileColor(const sigrid_coord::Coord& coord) const;

    float getRightPosition() const;

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ColorManager* m_tileColorManagerPtr = nullptr;
    ColorManager* m_highlightColorManagerPtr = nullptr;

    sigrid_list::AutoInsertMappedGrid<GraphicTile> m_tiles;

    sf::Vector2f m_tileSize = {0.f, 0.f};
    sf::Vector2f m_topLeftPosition = {0.f, 0.f};

    bool m_isLeftToRight = true;
    bool m_isTopToBottom = true;
};

}  // namespace sigrid