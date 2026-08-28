#pragma once

#include <optional>

#include "sigrid/utilities/Position/Position_f.h"
#include "sigrid/utilities/Offset/Offset_f.h"
#include "sigrid/utilities/lists/OrderedMap.h"

#include "sigrid/utilities/Coord/CoordPair.h"
#include "sigrid/Entity/Shape/Arrow/GraphicArrow.h"
#include "sigrid/Entity/Shape/Arrow/ArrowContainer.h"

namespace sigrid{

class LogicArrow;
class ColorManager;

class GraphicArrows: public sf::Drawable{

  public:

    GraphicArrows() = default;
    GraphicArrows(const GraphicArrows&) = default;
    GraphicArrows(GraphicArrows&&) = default;
    GraphicArrows& operator=(const GraphicArrows&) = default;
    GraphicArrows& operator=(GraphicArrows&&) = default;

    ArrowContainer getArrowContainer() const;

    void setThickness(const float& thickness);
    void setHeadSize(const float& headSize);
    void setColorManagerPtr(ColorManager* const managerPtr);

    void addArrow(const sigrid_coord::CoordPair& coordPair, const sigrid::Position_f& fromPosition, const sigrid::Position_f& toPosition, const LogicArrow& logicArrow);
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

    void move(const sigrid::Offset_f& offset);

  private:

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    ColorManager* m_colorManagerPtr = nullptr;

    sigrid_list::OrderedMap<sigrid_coord::CoordPair, GraphicArrow> m_arrows;

    float m_arrowThickness = 0.f;
    float m_arrowHeadSize = 0.f;
};

}  // namespace sigrid