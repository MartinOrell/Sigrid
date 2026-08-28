#pragma once

#include <optional>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Offset/Offset_f.h"
#include "sigrid/utilities/Coord/Coord.h"
#include "sigrid/utilities/lists/AutoInsertMappedGrid.h"
#include "sigrid/Entity/Tile/GraphicTile.h"
#include "sigrid/Entity/Tile/TileContainer.h"

namespace sigrid{
    
class ColorManager;

class GraphicTiles: public sf::Drawable{

  public:

    GraphicTiles() = default;
    GraphicTiles(const GraphicTiles&) = default;
    GraphicTiles(GraphicTiles&&) = default;
    GraphicTiles& operator=(const GraphicTiles&) = default;
    GraphicTiles& operator=(GraphicTiles&&) = default;

    TileContainer getTileContainer() const;

    void setColorManagerPtr(ColorManager* const managerPtr);
    void setHighlightColorManagerPtr(ColorManager* const managerPtr);

    void setNumColumns(const int& columns);
    void setNumRows(const int& rows);
    void setTileSize(const sigrid::Size_f& tileSize);
    void setTopLeftPosition(const sigrid::Position_f& topLeftPosition);

    void setLeftToRight();
    void setRightToLeft();
    void setTopToBottom();
    void setBottomToTop();

    void insertAllTiles();

    void setTilePosition(const sigrid_coord::Coord& coord, const sigrid::Position_f& position);

    void setTileColor(const sigrid_coord::Coord& coord, const int& colorId);

    void setHighlightColor(const sigrid_coord::Coord& coord, const int& colorId);
    void removeHighlight(const sigrid_coord::Coord& coord);

    void addColumnRight(const sigrid_list::Vector<int>& repeatTileColorIds);
    void addColumnLeft(const sigrid_list::Vector<int>& repeatTileColorIds);
    void removeRightColumn();
    void removeLeftColumn();
    void addRowUp(const sigrid_list::Vector<int>& repeatTileColorIds);
    void addRowDown(const sigrid_list::Vector<int>& repeatTileColorIds);
    void removeTopRow();
    void removeBottomRow();

    void clear();

    int getNumColumns() const;
    int getNumRows() const;

    float getTileWidth() const;
    float getTileHeight() const;
    sigrid::Size_f getTileSize() const;
    
    std::optional<sigrid::Position_f> getTileTopLeftPosition(const sigrid_coord::Coord& coord) const;
    std::optional<sigrid::Position_f> getTileCentrePosition(const sigrid_coord::Coord& coord) const;
    std::optional<float> getTileRightPosition(const sigrid_coord::Coord& coord) const;
    std::optional<float> getTileTopPosition(const sigrid_coord::Coord& coord) const;

    std::optional<sigrid::Color> getTileColor(const sigrid_coord::Coord& coord) const;

    float getRightPosition() const;

    void move(const sigrid::Offset_f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ColorManager* m_tileColorManagerPtr = nullptr;
    ColorManager* m_highlightColorManagerPtr = nullptr;

    sigrid_list::AutoInsertMappedGrid<GraphicTile> m_tiles;

    sigrid::Size_f m_tileSize = {0.f, 0.f};
    sigrid::Position_f m_topLeftPosition = {0.f, 0.f};

    bool m_isLeftToRight = true;
    bool m_isTopToBottom = true;
};

}  // namespace sigrid