#pragma once

#include <optional>

#include "List/OrderedMap.h"

#include "Coord/CoordPair.h"
#include "Entity/Shape/Arrow/GraphicArrow.h"

namespace sigrid{

class LogicArrow;
class ColorManager;

class GraphicArrows: public sf::Drawable{

  public:

    GraphicArrows();

    void setThickness(const float& thickness);
    void setHeadSize(const float& headSize);
    void setColorManagerPtr(ColorManager* const managerPtr);

    void addArrow(const sigrid_coord::CoordPair& coordPair, const sf::Vector2f& fromPosition, const sf::Vector2f& toPosition, const LogicArrow& logicArrow);
    void removeArrow(const sigrid_coord::CoordPair& coordPair);

    float getThickness() const;
    float getHeadSize() const;

    std::optional<GraphicArrow> getArrow(const sigrid_coord::CoordPair& coordPair) const;
    const sigrid_list::OrderedMap<sigrid_coord::CoordPair, GraphicArrow>& getArrows() const;
    sigrid_list::OrderedMap<sigrid_coord::CoordPair, GraphicArrow>& getArrows();

    void clear();

    void removeColumn(const int& columnId);
    void removeRow(const int& rowId);

    void moveArrowsRight(const float& tileWidth, const bool& isLeftToRight);
    void moveArrowsLeft(const float& tileWidth, const bool& isLeftToRight);
    void moveArrowsUp(const float& tileHeight, const bool& isTopToBottom);
    void moveArrowsDown(const float& tileHeight, const bool& isTopToBottom);

    void move(const sf::Vector2f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ColorManager* m_colorManagerPtr = nullptr;

    sigrid_list::OrderedMap<sigrid_coord::CoordPair, GraphicArrow> m_arrows;

    float m_arrowThickness = 0.f;
    float m_arrowHeadSize = 0.f;
};

}  // namespace sigrid